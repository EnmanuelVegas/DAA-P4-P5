/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/intra_swap.h"

std::pair<bool, SolutionPtr> IntraSwap::GetBestNeighbor(
    SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  // std::cout << "Entrada IntraSwap" << std::endl;
  double best_neighbor_time = solution->total_time();
  for (auto& vehicle : solution->vehicles()) {
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) {
      for (int j{i + 1}; j < route_size - 1; j++) {
        if ((instance->IsTransferStation(vehicle->route()[i])) ||
            (instance->IsTransferStation(vehicle->route()[j])) || i == j) {
          continue;
        }
        IntraSwapMovement candidate = {vehicle->id(), i, j};
        double new_time = GetNewTime(solution, candidate, instance);
        if (!(IsLess(new_time, best_neighbor_time))) {
          continue;
        }
        if (IsLegalMovement(solution, candidate, instance)) {
          movement_ = {vehicle->id(), i, j};
          best_neighbor_time = new_time;
        }
      }
    }
  }
  if (IsLess(best_neighbor_time, solution->total_time())) {
    // std::cout << "Del vehiculo " << movement_.vehicle_id << " la zona " <<
    // solution->vehicles()[movement_.vehicle_id -
    // 1]->route()[movement_.first_zone_id]->id()
    // << " swap con " << solution->vehicles()[movement_.vehicle_id -
    // 1]->route()[movement_.second_zone_id]->id() << std::endl;
    SolutionPtr best_neighbor = std::make_shared<Solution>(*solution);
    auto& route = best_neighbor->vehicles()[movement_.vehicle_id - 1]->route();
    std::swap(route[movement_.first_zone_id], route[movement_.second_zone_id]);
    best_neighbor->UpdateRouteTime(movement_.vehicle_id, instance);
    return {true, best_neighbor};
  }
  return {false, solution};
}

double IntraSwap::GetNewTime(SolutionPtr new_solution,
                             IntraSwapMovement movement,
                             std::shared_ptr<VRPInstance> instance) {
  double old_time = new_solution->total_time();
  std::vector<ZonePtr> route =
      new_solution->vehicles()[movement.vehicle_id - 1]->route();
  ZonePtr zone_1 = route[movement.first_zone_id];
  ZonePtr zone_2 = route[movement.second_zone_id];
  ZonePtr parent_zone_1 = route[movement.first_zone_id - 1];
  ZonePtr child_zone_1 = route[movement.first_zone_id + 1];
  ZonePtr parent_zone_2 = route[movement.second_zone_id - 1];
  ZonePtr child_zone_2 = route[movement.second_zone_id + 1];
  // Substracted
  double first_parent =
      instance->CalculateTime(parent_zone_1->id(), zone_1->id());
  double first_child =
      instance->CalculateTime(zone_1->id(), child_zone_1->id());
  double second_parent =
      instance->CalculateTime(parent_zone_2->id(), zone_2->id());
  double second_child =
      instance->CalculateTime(zone_2->id(), child_zone_2->id());
  double deleted_time =
      first_parent + first_child + second_parent + second_child;
  // std::cout << "Quitamos " << parent_zone_1->id() << " " << zone_1->id() <<
  // std::endl; std::cout << "Quitamos " << zone_1->id() << " " <<
  // child_zone_1->id() << std::endl; std::cout << "Quitamos " <<
  // parent_zone_2->id() << " " << zone_2->id() << std::endl; std::cout <<
  // "Quitamos " << zone_2->id() << " " << child_zone_2->id() << std::endl;
  // Added
  first_parent = instance->CalculateTime(parent_zone_1->id(), zone_2->id());
  // std::cout << "Agreg " << parent_zone_1->id() << " " << zone_2->id() <<
  // std::endl;
  if (std::abs(movement.first_zone_id - movement.second_zone_id) == 1) {
    // std::cout << "Agreg " << zone_2->id() << " " << zone_1->id() <<
    // std::endl; std::cout << "Agreg " << zone_2->id() << " " << zone_1->id()
    // << std::endl;
    first_child = instance->CalculateTime(zone_2->id(), zone_1->id());
    second_parent = instance->CalculateTime(zone_1->id(), zone_2->id());
  } else {
    // std::cout << "Agreg " << zone_2->id() << " " << child_zone_1->id() <<
    // std::endl; std::cout << "Agreg " << parent_zone_2->id() << " " <<
    // zone_1->id() << std::endl;
    first_child = instance->CalculateTime(zone_2->id(), child_zone_1->id());
    second_parent = instance->CalculateTime(parent_zone_2->id(), zone_1->id());
  }
  // std::cout << "Agreg " << zone_1->id() << " " << child_zone_2->id() <<
  // std::endl;
  second_child = instance->CalculateTime(zone_1->id(), child_zone_2->id());
  double added_time = first_parent + first_child + second_parent + second_child;
  // new_solution->vehicles()[movement.vehicle_id -
  // 1]->UpdateRouteTime(added_time - deleted_time); std::cout <<  "RESULT " <<
  // old_time - deleted_time + added_time << std::endl;
  return old_time - deleted_time + added_time;
}

bool IntraSwap::IsLegalMovement(SolutionPtr solution,
                                IntraSwapMovement movement,
                                std::shared_ptr<VRPInstance> instance) {
  auto route = solution->vehicles()[movement.vehicle_id - 1]->route();
  std::swap(route[movement.first_zone_id], route[movement.second_zone_id]);
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