/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file solution_generator.h: Declaracion de la clase 'SolutionGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/solution_generator.h"

SolutionPtr SolutionGenerator::GenerateSolution() {
  SolutionPtr best_solution;
  int counter{0};
  int not_improved{0};
  Timer timer = Timer();
  timer.StartStopwatch();
  while (counter++ < this->multistart_rep_) {
    SolutionPtr solution = BuildCollectionRoutes();
    solution = RandomVND(solution);
    solution->BuildTasks(instance_);
    solution = BuildTransferRoutes(solution);
    if (solution->IsBetter(best_solution)) {
      best_solution = solution;
      not_improved = 0;
    }
    if (not_improved >= this->multistart_rep_ * 0.1) {
      break;
    }
  }
  best_solution->CPU_time() = timer.FinishStopwatch();
  // std::cout << *best_solution;
  return best_solution;
}

SolutionPtr SolutionGenerator::BuildCollectionRoutes() {
  // Greedy Requirements
  std::vector<ZonePtr> zones = instance_->collection_zones();
  double collection_capacity = instance_->collection_capacity();
  double max_time = instance_->max_collection_time();
  ZonePtrPair transport_zones = instance_->transfer_stations();
  ZonePtr depot = instance_->depot();
  // Greedy execution
  SolutionPtr solution = std::make_shared<Solution>();
  int vehicle_index = 1;
  while (!zones.empty()) {
    CollectionVehiclePtr current_vehicle = std::make_shared<CollectionVehicle>(
        vehicle_index, max_time, collection_capacity);
    current_vehicle->AddStop(depot);
    while (true) {
      ZonePtr last_stop = current_vehicle->route().back();
      // std::cout << std::endl << "Fuera: " << last_stop->id() << std::endl;
      ZonePtr closest = SelectClosestZone(last_stop, zones);
      if (closest == nullptr) {
        break;
      }
      double return_depot_time = ReturnToDepotTime(last_stop, closest);
      if (closest->waste_quantity() <= current_vehicle->remaining_capacity() &&
          return_depot_time <= current_vehicle->remaining_time()) {
        AddNormalStop(last_stop, closest, current_vehicle);
        zones.erase(find(zones.begin(), zones.end(), closest));
      } else if (return_depot_time <= current_vehicle->remaining_time()) {
        ZonePtr closest_transfer =
            SelectClosestTransferStation(last_stop->id());
        AddTransferStop(last_stop, closest_transfer, current_vehicle,
                        collection_capacity, max_time);
      } else {
        break;
      }
    }
    ZonePtr last_stop = current_vehicle->route().back();
    if (!instance_->IsTransferStation(last_stop)) {
      ZonePtr closest_transport = SelectClosestTransferStation(last_stop->id());
      AddTransferStop(last_stop, closest_transport, current_vehicle,
                      collection_capacity, max_time);
      AddNormalStop(closest_transport, depot, current_vehicle);
    } else {
      AddNormalStop(last_stop, depot, current_vehicle);
    }
    solution->PushCollectionVehicle(current_vehicle);
    vehicle_index++;
  }
  return solution;
}

SolutionPtr SolutionGenerator::RandomVND(SolutionPtr solution) {
  search_selector_.Reset();
  int old_time = solution->total_time();
  // std::string result = "\n--- Random VND ---\nImproved solutions:\n";
  while (!this->search_selector_.IsEmpty()) {
    std::shared_ptr<LocalSearch> search_method = search_selector_.SelectMethod();
    // result += "Cambiamos a " + search_method->type();
    bool improved_local{false};
    while (true) {
      std::pair<bool, SolutionPtr> search_result{search_method->GetBestNeighbor(solution, this->instance_)};
      if (search_result.first) {
        // result +=  "- Time: ";
        // result +=  std::to_string(solution->total_time()) + " --> ";
        solution = search_result.second;
        // result +=  std::to_string(solution->total_time()) + " \n";
        improved_local = true;
        continue;
      } else if (improved_local) {
        // result += "Reset!\n";
        this->search_selector_.Reset();
        break;
      } else {
        break;
      }
    }
  }
  // if (solution->total_time() < old_time) {
  //   std::cout << result;
  // }
  return solution;
}

TransportVehiclePtr ChooseVehicle(std::vector<TransportVehiclePtr>& candidates,
                                  TaskPtr task, VRPInstancePtr instance,
                                  double max_duration) {
  TransportVehiclePtr chosen = nullptr;
  double insertion_cost{std::numeric_limits<double>::max()};
  double zone_time_transport;
  double arrival_time;
  double waiting_time;

  for (auto& candidate : candidates) {
    // Condition a)
    if (!candidate->tasks().empty()) {
      int last_task_stop = candidate->tasks().back()->transfer_id();
      double last_task_time = candidate->tasks().back()->time();
      double current_task_time = task->time();
      double travel_time =
          instance->CalculateTime(last_task_stop, task->transfer_id());
      if (travel_time > (current_task_time - last_task_time)) {
        // std::cout << "CONDITION A\n";
        continue;
      }
    }
    // Condition b)
    if (candidate->remaining_capacity() < task->waste()) {
      // std::cout << "CONDITION B\n";
      continue;
    }
    // Condition c)
    double zone_travel_time = instance->CalculateTime(
        candidate->route().back()->id(), task->transfer_id());
    double return_depot_time = instance->CalculateTime(
        task->transfer_id(), instance->dumpsite()->id());
    waiting_time = task->time() - candidate->TimeUsed() - zone_travel_time;
    if (waiting_time < 0) {
      waiting_time = 0;
    }
    double available_time = candidate->TimeLeft() -
                            (zone_travel_time + return_depot_time) -
                            waiting_time;
    double arrival_time = candidate->TimeUsed() + zone_travel_time;
    if (available_time > 0 && arrival_time < task->time()) {
      // Update
      if (zone_travel_time < insertion_cost) {
        chosen = candidate;
        insertion_cost = zone_travel_time;
      }
    }
  }
  return chosen;
}

SolutionPtr SolutionGenerator::BuildTransferRoutes(SolutionPtr solution) {
  double max_capacity = instance_->transport_capacity();
  double max_duration = instance_->max_transport_time();
  auto tasks = solution->tasks();
  std::sort(tasks.begin(), tasks.end(), [](const TaskPtr& a, const TaskPtr& b) {
    return a->time() < b->time();
  });
  std::vector<TransportVehiclePtr> transport_vehicles(0);
  double min_waste = std::numeric_limits<double>::max();
  for (const auto& task : tasks) {
    min_waste = std::min(min_waste, task->waste());
  }
  double new_zone_time{0}, arrival_time{0}, waiting_time{0};
  while (!tasks.empty()) {
    TaskPtr task = tasks.front();
    // std::cout << "Task: " << *task;
    tasks.erase(tasks.begin());
    TransportVehiclePtr vehicle =
        ChooseVehicle(transport_vehicles, task, instance_, max_duration);
    if (vehicle == nullptr) {
      int new_vehicle_id = transport_vehicles.size() + 1;
      vehicle = std::make_shared<TransportVehicle>(new_vehicle_id, max_duration,
                                                   max_capacity);
      vehicle->AddStop(instance_->dumpsite());
      transport_vehicles.push_back(vehicle);
    }
    // std::cout << "Asignado a " << vehicle->id() << "\n";
    new_zone_time = instance_->CalculateTime(vehicle->route().back()->id(),
                                             task->transfer_id());
    arrival_time = vehicle->TimeUsed() + new_zone_time;
    waiting_time = task->time() - arrival_time;
    double total_time = new_zone_time;
    if (waiting_time > 0) {
      total_time += waiting_time;
    }
    vehicle->AddStop(instance_->single_transfer_station(task->transfer_id()));
    vehicle->DiminishCapacity(task->waste());
    vehicle->UpdateTime(total_time);
    if (vehicle->route().size() == 2) {
      double depot_to_first_zone = instance_->CalculateTime(
          instance_->dumpsite()->id(), task->transfer_id());
      double departure_time = task->time() - depot_to_first_zone;
      if (departure_time >= 0) {
        vehicle->departure_time() = departure_time;
      }
    }
    if (vehicle->remaining_capacity() < min_waste) {
      vehicle->UpdateTime(instance_->CalculateTime(vehicle->route().back()->id(), instance_->dumpsite()->id()));
      vehicle->AddStop(instance_->dumpsite());
      vehicle->RestoreCapacity();
    }
    vehicle->AssignTask(task);
  }
  for (auto& vehicle : transport_vehicles) {
    if (vehicle->route().back()->id() != instance_->dumpsite()->id()) {
      vehicle->UpdateTime(instance_->CalculateTime(vehicle->route().back()->id(), instance_->dumpsite()->id()));
      vehicle->AddStop(instance_->dumpsite());
    }
  }
  solution->AssignTransportVehicles(transport_vehicles);
  return solution;
}

double SolutionGenerator::CalculateRoutesTime(SolutionPtr solution) {
  double total_time{0};
  for (auto& vehicle : solution->vehicles()) {
    total_time += instance_->max_collection_time() - vehicle->remaining_time();
    // Otra forma de calcularlo: Recalculando todos los tiempos de la ruta.
    // std::vector<ZonePtr> route = vehicle->route();
    // for (auto& stop : route) {
    //   total_time += CalculateTime(...);
    // }
  }
  return total_time;
}

double SolutionGenerator::ReturnToDepotTime(ZonePtr actual_zone,
                                            ZonePtr closest) {
  // time_1 = Current zone to closest collection zone.
  double time_1 = instance_->CalculateTime(actual_zone->id(), closest->id()) +
                  closest->process_time();
  ZonePtr transfer = SelectClosestTransferStation(closest->id());
  // time_2 = closest collection to closest SWTS.
  double time_2 = instance_->CalculateTime(closest->id(), transfer->id());
  // time_3 = SWTS to depot.
  double time_3 =
      instance_->CalculateTime(transfer->id(), instance_->depot()->id());
  return time_1 + time_2 + time_3;
}

ZonePtr SolutionGenerator::SelectClosestZone(ZonePtr zone,
                                             std::vector<ZonePtr>& candidates) {
  if (candidates.empty()) {
    return nullptr;
  }
  std::vector<std::tuple<double, int, ZonePtr>> distances;
  int index = 0;
  for (const auto& candidate : candidates) {
    if (zone->id() != candidate->id()) {
      double distance = instance_->GetDistance(zone->id(), candidate->id());
      distances.emplace_back(distance, index, candidate);
    }
    ++index;
  }
  std::sort(
      distances.begin(), distances.end(),
      [](const std::tuple<double, int, ZonePtr>& a,
         const std::tuple<double, int, ZonePtr>& b) {
        if (std::get<0>(a) == std::get<0>(b)) {
          return std::get<1>(a) < std::get<1>(b);
        }
        return std::get<0>(a) < std::get<0>(b);
      });

  // for (auto& num : distances) {
  //   std::cout << "(" << num.second->id() << " " << num.first << ") ";
  // }
      
  if (distances.size() > this->candidates_size_) {
    distances.resize(this->candidates_size_);
  }
  std::uniform_int_distribution<> dis(0, distances.size() - 1);
  int random_index = dis(this->gen_);
  // for (auto& num : distances) {
  //   std::cout << num.second->id() << " ";
  // }
  // std::cout << "Seleccionamos: " << distances[random_index].second->id() << "\n";
  // std::cout << "Indice seleccionado: " << random_index << "\n";
  return std::get<2>(distances[random_index]);
}

void SolutionGenerator::AddNormalStop(ZonePtr last, ZonePtr closest,
                                      CollectionVehiclePtr vehicle) {
  double visit_closest_time =
      instance_->CalculateTime(last->id(), closest->id());
  // std::cout << "la candidata es " << closest->id() << std::endl;
  // std::cout << "el tiempo para llegar hasta ella es de " <<
  // visit_closest_time << " minutos y tenemos " << vehicle->remaining_time() <<
  // " minutos." << std::endl; std::cout << "el tiempo para volver si la
  // añadimos es de  " << tiempo_en_regresar << " minutos y tenemos " <<
  // vehicle->remaining_time() << " minutos." << std::endl; std::cout << "la
  // carga que añade es de " << closest->waste_quantity() << " y la capacidad
  // restante del camión es de " << vehicle->remaining_capacity() << std::endl;
  vehicle->AddStop(closest);  // It also substracts the capacity.
  vehicle->UpdateTime(visit_closest_time + closest->process_time());
  return;
}

void SolutionGenerator::AddTransferStop(ZonePtr last, ZonePtr transfer,
                                        CollectionVehiclePtr vehicle,
                                        double capacity, double max_time) {
  double visit_transfer_time =
      instance_->CalculateTime(last->id(), transfer->id());
  vehicle->UpdateTime(visit_transfer_time);

  vehicle->AddStop(transfer);
  vehicle->RestoreCapacity();
  return;
}

ZonePtr SolutionGenerator::SelectClosestTransferStation(int zone_id) {
  // if (zones.size() == 0) { return anchor; }
  double distance_first = instance_->GetDistance(
      zone_id, instance_->transfer_stations().first->id());
  double distance_second = instance_->GetDistance(
      zone_id, instance_->transfer_stations().second->id());
  if (distance_first <= distance_second) {
    return instance_->transfer_stations().first;
  }
  return instance_->transfer_stations().second;
}