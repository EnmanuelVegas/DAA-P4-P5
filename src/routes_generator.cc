/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/routes_generator.h"

SolutionPtr RoutesGenerator::GenerateGRASP() {
  // std::vector<VehiclePtr> best_solution = this->GenerateGreedy();
  SolutionPtr best_solution;
  double best_time{std::numeric_limits<double>::max()};
  for (int i{0}; i < 3; i++) { // CAMBIAR A 5 Y 100
    std::cout << "\nGRASP: Iteration " << i + 1<< ":\n";
    SolutionPtr best_local;
    double best_local_time{std::numeric_limits<double>::max()};
    for (int j{0}; j < 10; j++) {
      SolutionPtr solution = this->GenerateSingleRoute();
      solution = PerformLocalSearch(solution);
      double solution_time{CalculateRoutesTime(solution)};
      if (solution_time < best_local_time) {
        best_local = solution;
        best_local_time = solution_time;
      }
      // std::cout << solution_time << std::endl; // VERIFY RANDOMNESS
    }
    // double solution_time{CalculateRoutesTime(best_local)};
    std::cout << "Local best: " << best_local_time << "\n";
    if (best_local_time < best_time) {
      best_solution = best_local;
      best_time = best_local_time;
    }
  }
  std::cout << "Best global solution: ";
  // std::cout << best_solution->total_time() << std::endl;
  std::cout << *best_solution << std::endl;
  return best_solution;
}


SolutionPtr RoutesGenerator::GenerateSingleRoute() {
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
    VehiclePtr current_vehicle = std::make_shared<Vehicle>(vehicle_index, max_time, collection_capacity);
    current_vehicle->AddStop(depot);
    while (true) {
      ZonePtr last_stop = current_vehicle->route().back();
      ZonePtr closest = SelectClosestZone(last_stop, zones);
      if (closest == nullptr) { break; }
      double return_depot_time = ReturnToDepotTime(last_stop, closest);
      if (closest->waste_quantity() <= current_vehicle->remaining_capacity() &&
          return_depot_time <= current_vehicle->remaining_time()) {
        AddNormalStop(last_stop, closest, current_vehicle);
        zones.erase(find(zones.begin(), zones.end(), closest));
      } else if (return_depot_time <= current_vehicle->remaining_time()) {
        ZonePtr closest_transfer = SelectClosestTransferStation(last_stop->id()); // REVISAR CON EL PSEUDOCÓDIGO: last_stop o closest_zone?
        AddTransferStop(last_stop, closest_transfer, current_vehicle, collection_capacity, max_time);        
      } else {
        break;
      }
    }
    ZonePtr last_stop = current_vehicle->route().back();
    if (!instance_->IsTransferStation(last_stop)) {
      ZonePtr closest_transport = SelectClosestTransferStation(last_stop->id());
      AddTransferStop(last_stop, closest_transport, current_vehicle, collection_capacity, max_time);
      AddNormalStop(closest_transport, depot, current_vehicle);
    } else {
      AddNormalStop(last_stop, depot, current_vehicle);
    }
    solution->PushVehicle(current_vehicle);
    vehicle_index++;
  }
  return solution;
}

SolutionPtr RoutesGenerator::PerformLocalSearch(SolutionPtr solution) {
  std::shared_ptr<LocalSearch> search_method = std::make_shared<InterReinsertion>();
  // std::string result = "\n--- LOCAL SEARCH ---\nImproved solutions:\n";
  std::cout << "\n--- LOCAL SEARCH ---\nImproved solutions:\n";
  // bool improved{false};
  while (true) {
    std::pair<bool, SolutionPtr> search_result{search_method->Apply(solution, this->instance_)};
    if (search_result.first) {
      std::cout <<  " Before: \n";
      std::cout << *solution;
      std::cout <<  "- Time: ";
      std::cout <<  std::to_string(solution->total_time()) + " --> ";
      solution = search_result.second;
      std::cout <<  std::to_string(solution->total_time()) + " \n";
      std::cout << *solution;
      // improved = true;
    }
    else {
      break;
    }
  }
  // if (improved) {
  //   std::cout << result;
  // }
  return solution;
}

 

double RoutesGenerator::CalculateRoutesTime(SolutionPtr solution) {
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

double RoutesGenerator::ReturnToDepotTime(ZonePtr actual_zone, ZonePtr closest) {
  // time_1 = Current zone to closest collection zone.
  double time_1 = instance_->CalculateTime(actual_zone->id(), closest->id()) + closest->process_time();
  ZonePtr transfer = SelectClosestTransferStation(closest->id());
  // time_2 = closest collection to closest SWTS.
  double time_2 = instance_->CalculateTime(closest->id(), transfer->id());
  // time_3 = SWTS to depot.
  double time_3 = instance_->CalculateTime(transfer->id(), instance_->depot()->id());
  return time_1 + time_2 + time_3;
}

ZonePtr RoutesGenerator::SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates) {
  if (candidates.empty()) {
    return nullptr;
  }
  // Crear un vector de pares (distancia, ZonePtr)
  std::vector<std::pair<double, ZonePtr>> distances;
  for (const auto& candidate : candidates) {
    if (zone->id() != candidate->id()) {  // Evitar comparar con la misma zona
      double distance = instance_->GetDistance(zone->id(), candidate->id());
      distances.emplace_back(distance, candidate);
    }
  }
  // Ordenar los candidatos por distancia
  std::sort(distances.begin(), distances.end(),
            [](const std::pair<double, ZonePtr>& a, const std::pair<double, ZonePtr>& b) {
              return a.first < b.first;
            });
  // Limitar a los `n` elementos más cercanos
  if (distances.size() > this->candidates_size_) {
    distances.resize(this->candidates_size_);
  }
  // Seleccionar aleatoriamente uno de los `n` elementos más cercanos
  std::uniform_int_distribution<> dis(0, distances.size() - 1);  // Crear la distribución
  int random_index = dis(this->gen_);
  // for (auto& num : distances) {
  //   std::cout << num.second->id() << " ";
  // }
  // std::cout << "Seleccionamos: " << distances[random_index].second->id();
  // std::cout << "\n";
  // std::cout << "Indice seleccionado: " << random_index << " ";
  return distances[random_index].second;  // Retornar el ZonePtr seleccionado
}

void RoutesGenerator::AddNormalStop(ZonePtr last, ZonePtr closest, VehiclePtr vehicle) {
  double visit_closest_time = instance_->CalculateTime(last->id(), closest->id());
  // std::cout << "la candidata es " << closest->id() << std::endl;
  // std::cout << "el tiempo para llegar hasta ella es de " << visit_closest_time << " minutos y tenemos " << vehicle->remaining_time() << " minutos." << std::endl;
  // std::cout << "el tiempo para volver si la añadimos es de  " << tiempo_en_regresar << " minutos y tenemos " << vehicle->remaining_time() << " minutos." << std::endl;
  // std::cout << "la carga que añade es de " << closest->waste_quantity() << " y la capacidad restante del camión es de " << vehicle->remaining_capacity() << std::endl;
  vehicle->AddStop(closest);  // It also substracts the capacity.
  vehicle->UpdateTime(visit_closest_time + closest->process_time());  
  return;
}

void RoutesGenerator::AddTransferStop(ZonePtr last, ZonePtr transfer, VehiclePtr vehicle,
                                     double capacity, double max_time) {
  double visit_transfer_time = instance_->CalculateTime(last->id(), transfer->id());
  vehicle->UpdateTime(visit_transfer_time);

  vehicle->AddTask(std::make_shared<Task>(capacity - vehicle->remaining_capacity(),
                   transfer->id(), max_time - vehicle->remaining_time()));
  vehicle->AddStop(transfer);
  vehicle->RestoreCapacity();
  return;
}

ZonePtr RoutesGenerator::SelectClosestTransferStation(int zone_id) {
  // if (zones.size() == 0) { return anchor; }
  double distance_first = instance_->GetDistance(zone_id, instance_->transfer_stations().first->id());
  double distance_second = instance_->GetDistance(zone_id, instance_->transfer_stations().second->id());
  if (distance_first <= distance_second) {
    return instance_->transfer_stations().first;
  }
  return instance_->transfer_stations().second;
}