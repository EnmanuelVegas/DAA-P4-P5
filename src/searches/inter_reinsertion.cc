/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/inter_reinsertion.h"

std::pair<bool, SolutionPtr> InterReinsertion::GetLocalOptimum(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  std::cout << *solution;
  std::cout << "Entrada InterReinsertion" << std::endl;
  double best_neighbor_time = solution->total_time();
  // SolutionPtr local_optimal = std::make_shared<Solution>(*solution);
  int hola;
  int vehicles_size{int(solution->vehicles().size())};
  for (int i{0}; i < vehicles_size; i++) {
    auto vehicle = solution->vehicles()[i];
    int route_size{int(vehicle->route().size())};
    for (int k{1}; k < route_size - 1; k++) { // From 1 to route size - 2 to avoid mixing the depots
      for (int l{0}; l < vehicles_size; l++) {
        auto other_vehicle = solution->vehicles()[l];
        int other_route_size{int(other_vehicle->route().size())};
        for (int m{1}; m < other_route_size - 1; m++) { // From 1 to route size - 2 to avoid mixing the depots  
          if (instance->IsTransferStation(vehicle->route()[k]) ||
              instance->IsTransferStation(other_vehicle->route()[m]) ||
              vehicle->id() == other_vehicle->id()) {
            continue;
          }
          // std::cout << "Movimiento: Vehiculo " << i + 1 << ", otro " << l + 1 << ", first: " << vehicle->route()[k]->id() << ", second:" << other_vehicle->route()[m]->id() << std::endl;
          InterReinsertionMovement candidate = {vehicle->id(), other_vehicle->id(), k, m};
          InterReinsertionTimes new_times = GetNewTime(solution, candidate, instance);
          if (!(IsLess(new_times.whole_time, best_neighbor_time))) {
            continue;
          }
          if (CheckMovement(solution, new_times, instance)) {
            std::cout << "CANDIDATO: Vehiculo " << i + 1 << ", otro " << l + 1 << ", first: " << vehicle->route()[k]->id() << ", second:" << other_vehicle->route()[m]->id() << std::endl;
            movement_ = candidate;
            best_neighbor_time = new_times.whole_time;
            // std::cin >> hola;
          }
        }
      }
    }
  }
  if (IsLess(best_neighbor_time, solution->total_time())) {
    // std::cout << "Entrada If final" << std::endl;
    SolutionPtr best_neighbor = std::make_shared<Solution>(*solution);
    auto& first_route = best_neighbor->vehicles()[movement_.delete_vehicle_id - 1]->route();
    auto& second_route = best_neighbor->vehicles()[movement_.insert_vehicle_id - 1]->route();
    ZonePtr zone = first_route[movement_.delete_zone_id];
    first_route.erase(first_route.begin() + movement_.delete_zone_id);
    second_route.insert(second_route.begin() + movement_.insert_zone_id, zone);
    best_neighbor->UpdateTotalTime(movement_.delete_vehicle_id, instance);
    best_neighbor->UpdateTotalTime(movement_.insert_vehicle_id, instance);
    // std::cout << "alida If final" << std::endl;
    return {true, best_neighbor};
  }
  return {false, solution};
}  

InterReinsertionTimes InterReinsertion::GetNewTime(SolutionPtr solution, InterReinsertionMovement movement, std::shared_ptr<VRPInstance> instance) {
  // std::cout << "Get New Time" << std::endl;
  InterReinsertionTimes times;
  times.movement = movement;
  double old_time = solution->total_time();
  std::vector<ZonePtr> first_route = solution->vehicles()[movement.delete_vehicle_id - 1]->route();
  std::vector<ZonePtr> second_route = solution->vehicles()[movement.insert_vehicle_id - 1]->route();
  times.delete_route_time = solution->vehicles()[movement.delete_vehicle_id - 1]->TimeUsed();
  times.insert_route_time = solution->vehicles()[movement.insert_vehicle_id - 1]->TimeUsed();
  ZonePtr zone_delete = first_route[movement.delete_zone_id];
  ZonePtr zone_insert = second_route[movement.insert_zone_id];
  ZonePtr parent_zone_delete = first_route[movement.delete_zone_id - 1];
  ZonePtr child_zone_delete = first_route[movement.delete_zone_id + 1];
  ZonePtr parent_zone_insert = second_route[movement.insert_zone_id - 1];
  ZonePtr child_zone_insert = second_route[movement.insert_zone_id + 1];
  // Substracted
  double delete_1 = instance->CalculateTime(parent_zone_delete->id(), zone_delete->id());
  double delete_2 = instance->CalculateTime(zone_delete->id(), child_zone_delete->id());
  times.delete_route_time -= (delete_1 + delete_2);
  times.delete_route_time -= zone_delete->process_time();
  double delete_3 = instance->CalculateTime(parent_zone_insert->id(), zone_insert->id());
  times.insert_route_time -= delete_3;
  double deleted_time = delete_1 + delete_2 + delete_3;
  // std::cout << "Quitamos " << parent_zone_delete->id() << " " << zone_delete->id() <<" Costo: "<< delete_1 <<  std::endl;
  // std::cout << "Quitamos " << zone_delete->id() << " " << child_zone_delete->id() <<" Costo: " << delete_2 << std::endl;
  // std::cout << "Quitamos " << parent_zone_insert->id() << " " << zone_insert->id() <<" Costo: " << delete_3 << std::endl;
  // Added
  double insert_1 = instance->CalculateTime(parent_zone_delete->id(), child_zone_delete->id());
  double insert_2 = instance->CalculateTime(zone_delete->id(), zone_insert->id());
  double insert_3 = instance->CalculateTime(parent_zone_insert->id(), zone_delete->id());
  times.delete_route_time += insert_1;
  times.insert_route_time += (insert_2 + insert_3);
  times.insert_route_time += zone_delete->process_time();
  double added_time = insert_1 + insert_2 + insert_3;
  // std::cout << "Agreg " << parent_zone_delete->id() << " " << child_zone_delete->id() << " Costo: " << insert_1 << std::endl;
  // std::cout << "Agreg " << zone_delete->id() << " " << zone_insert->id() << " Costo: " << insert_2 << std::endl;
  // std::cout << "Agreg " << parent_zone_insert->id() << " " << zone_delete->id() << " Costo: " << insert_3 << std::endl;
  // std::cout <<  "RESULT " << old_time - deleted_time + added_time << std::endl;
  times.whole_time = old_time - deleted_time + added_time;
  // std::cout << "Salida Get New Time" << std::endl;
  return times;
}


bool InterReinsertion::CheckMovement(SolutionPtr solution, InterReinsertionTimes times, std::shared_ptr<VRPInstance> instance) {
  // std::cout << "CheckMovement" << std::endl;
  if (times.delete_route_time > instance->max_collection_time() ||
      times.insert_route_time > instance->max_collection_time()) {
    return false;
  }
  InterReinsertionMovement candidate = times.movement;
  auto first_route = solution->vehicles()[candidate.delete_vehicle_id - 1]->route();
  auto second_route = solution->vehicles()[candidate.insert_vehicle_id - 1]->route();
  ZonePtr zone = first_route[candidate.delete_zone_id];
  first_route.erase(first_route.begin() + candidate.delete_zone_id);
  second_route.insert(second_route.begin() + candidate.insert_zone_id, zone);
  double waste{0};
  for (auto zone : first_route) {
    if (instance->IsTransferStation(zone)) {
      waste = 0;
    }
    waste += zone->waste_quantity();
    if (waste > instance->collection_capacity()) {
      return false;
    }
  }
  waste = 0;
  for (auto zone : second_route) {
    if (instance->IsTransferStation(zone)) {
      waste = 0;
    }
    waste += zone->waste_quantity();
    if (waste > instance->collection_capacity()) {
      return false;
    }
  }
  // std::cout << "Salida Check" << std::endl;
  return true;
}