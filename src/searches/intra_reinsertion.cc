/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/intra_reinsertion.h"

std::pair<bool, SolutionPtr> IntraReinsertion::GetLocalOptimum(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  // std::cout << *solution;
  // std::cout << "Entrada IntraSwap" << std::endl;
  int pr;
  double best_neighbor_time = solution->total_time();
  for (auto& vehicle : solution->vehicles()) {
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) { // From 1 to route size - 2 to avoid mixing the depots
      for (int j{1}; j < route_size - 1; j++) {
        if ((instance->IsTransferStation(vehicle->route()[i])) || 
            (instance->IsTransferStation(vehicle->route()[j])) || 
            i == j) {
          continue;
        }
        IntraReinsertionMovement candidate = {vehicle->id(), i, j};
        double new_time = GetNewTime(solution, candidate, instance);
        if (!(new_time < best_neighbor_time)) {
          continue;
        }
        // std::cout << "CANDIDATO: Vehiculo " << vehicle->id() << ", delete: " << vehicle->route()[i]->id() << ", insert in:" << vehicle->route()[j]->id() << std::endl;
        std::cout << new_time << std::endl;
        if (CheckMovement(solution, candidate, instance)) {
        // //  std::cout << "CANDIDATO: Vehiculo " << vehicle->id() << ", delete: " << vehicle->route()[i]->id() << ", insert in:" << vehicle->route()[j]->id() << std::endl;
          // std::cout << "Es buena!" << std::endl;
          movement_ = {vehicle->id(), i, j};
          best_neighbor_time = new_time;
        }
      }
    }
  }
  std::cout << best_neighbor_time << std::endl;
  // std::cin >> pr;
  if (best_neighbor_time < solution->total_time()) {
    // std::cout << "Mejora: Vehiculo " << movement_.vehicle_id << ", delete: " << movement_.delete_pos << ", insert in:" << movement_.insert_pos << std::endl;
    SolutionPtr best_neighbor = std::make_shared<Solution>(*solution);
    auto& route = best_neighbor->vehicles()[movement_.vehicle_id - 1]->route();
    ZonePtr zone = route[movement_.delete_pos];
    route.erase(route.begin() + movement_.delete_pos);
    route.insert(route.begin() + movement_.insert_pos, zone);
    best_neighbor->UpdateTotalTime(movement_.vehicle_id, instance);
    return {true, best_neighbor};
  }
  return {false, solution};
}

double IntraReinsertion::GetNewTime(SolutionPtr new_solution, IntraReinsertionMovement movement, std::shared_ptr<VRPInstance> instance) {
  double old_time = new_solution->total_time();
  std::vector<ZonePtr> route = new_solution->vehicles()[movement.vehicle_id - 1]->route();
  ZonePtr zone_delete = route[movement.delete_pos];
  ZonePtr zone_insert = route[movement.insert_pos];
  ZonePtr parent_zone_delete = route[movement.delete_pos - 1];
  ZonePtr child_zone_delete = route[movement.delete_pos + 1];
  ZonePtr parent_zone_insert = route[movement.insert_pos - 1];
  ZonePtr child_zone_insert = route[movement.insert_pos + 1];
  double delete_1, delete_2, delete_3, insert_1, insert_2, insert_3;
  // Substracted
  delete_1 = instance->CalculateTime(parent_zone_delete->id(), zone_delete->id());
  delete_2 = instance->CalculateTime(zone_delete->id(), child_zone_delete->id());
  if (movement.delete_pos > movement.insert_pos) {
    delete_3 = instance->CalculateTime(parent_zone_insert->id(), zone_insert->id());
  }
  else {
    delete_3 = instance->CalculateTime(zone_insert->id(), child_zone_insert->id());
  }
  double deleted_time = delete_1 + delete_2 + delete_3;
  // std::cout << "Quitamos " << parent_zone_delete->id() << " " << zone_delete->id() << std::endl;
  // std::cout << "Quitamos " << zone_delete->id() << " " << child_zone_delete->id() << std::endl;
  // std::cout << "Quitamos " << zone_insert->id() << " " << child_zone_insert->id() << std::endl;
  // Added
  insert_1 = instance->CalculateTime(parent_zone_delete->id(), child_zone_delete->id());
  insert_2 = instance->CalculateTime(zone_insert->id(), zone_delete->id());
  if (movement.delete_pos > movement.insert_pos) {
    insert_3 = instance->CalculateTime(parent_zone_insert->id(), zone_delete->id());
  }
  else {
    insert_3 = instance->CalculateTime(zone_delete->id(), child_zone_insert->id());
  }
  double added_time = insert_1 + insert_2 + insert_3;
  // std::cout << "Agreg " << parent_zone_delete->id() << " " << child_zone_insert->id() << std::endl;
  // std::cout << "Agreg " << zone_insert->id() << " " << zone_delete->id() << std::endl;
  // std::cout << "Agreg " << zone_delete->id() << " " << child_zone_insert->id() << std::endl;
  return old_time - deleted_time + added_time;
}


bool IntraReinsertion::CheckMovement(SolutionPtr solution, IntraReinsertionMovement candidate, std::shared_ptr<VRPInstance> instance) {
  auto route = solution->vehicles()[candidate.vehicle_id - 1]->route();

  // for (auto vehicle : route) {
  //   std::cout << vehicle->id() << " ";
  // }
  // std::cout << std::endl;

  ZonePtr zone = route[candidate.delete_pos];
  route.erase(route.begin() + candidate.delete_pos);
  route.insert(route.begin() + candidate.insert_pos, zone);

  // for (auto vehicle : route) {
  //   std::cout << vehicle->id() << " ";
  // }
  // std::cout << std::endl;

  double waste{0};
  for (auto zone : route) {
    if (instance->IsTransferStation(zone)) {
      waste = 0;
    }
    waste += zone->waste_quantity();
    if (waste > instance->collection_capacity()) {
      return false;
    }
  }
  return true;
}