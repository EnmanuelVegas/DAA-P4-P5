/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/inter_swap.h"

#include <iomanip>

std::pair<bool, SolutionPtr> InterSwap::GetBestNeighbor(
    SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  // std::cout << *solution;
  // std::cout << "Entrada InterSwap" << std::endl;
  double best_neighbor_time = solution->total_time();
  int vehicles_size{int(solution->vehicles().size())};
  for (int i{0}; i < vehicles_size; i++) {
    auto vehicle = solution->vehicles()[i];
    int route_size{int(vehicle->route().size())};
    for (int k{1}; k < route_size - 1; k++) {
      for (int l{i + 1}; l < vehicles_size; l++) {
        auto other_vehicle = solution->vehicles()[l];
        int other_route_size{int(other_vehicle->route().size())};
        for (int m{1}; m < other_route_size - 1; m++) {
          if ((instance->IsTransferStation(vehicle->route()[k])) ||
              (instance->IsTransferStation(other_vehicle->route()[m]))) {
            continue;
          }
          // std::cout << "Movimiento: Vehiculo " << i + 1 << ", otro " << l + 1
          // << ", first: " << vehicle->route()[k]->id() << ", second:" <<
          // other_vehicle->route()[m]->id() << std::endl;
          InterSwapMovement candidate = {vehicle->id(), other_vehicle->id(), k,
                                         m};
          InterSwapTimes new_times = GetNewTime(solution, candidate, instance);
          // std::cout << "De nuevo en bucle grande" << std::endl;
          if (!(IsLess(new_times.whole_time, best_neighbor_time))) {
            continue;
          }
          if (IsLegalMovement(solution, new_times, instance)) {
            // std::cout << "CANDIDATO: Vehiculo " << i + 1 << ", otro " << l +
            // 1 << ", first: " << vehicle->route()[k]->id() << ", second:" <<
            // other_vehicle->route()[m]->id() << std::endl;
            movement_ = candidate;
            best_neighbor_time = new_times.whole_time;
          }
        }
      }
    }
  }
  if (IsLess(best_neighbor_time, solution->total_time())) {
    // std::cout << "Del vehículo " << movement_.first_vehicle_id << " con
    // vehiculo "
    // << movement_.second_vehicle_id << " swap de " <<
    // solution->vehicles()[movement_.first_vehicle_id -
    // 1]->route()[movement_.first_route_zone_id]->id()
    //  << " con " << solution->vehicles()[movement_.second_vehicle_id -
    //  1]->route()[movement_.second_route_zone_id]->id() << std::endl;
    SolutionPtr best_neighbor = std::make_shared<Solution>(*solution);
    auto& first_route =
        best_neighbor->vehicles()[movement_.first_vehicle_id - 1]->route();
    auto& second_route =
        best_neighbor->vehicles()[movement_.second_vehicle_id - 1]->route();
    std::swap(first_route[movement_.first_route_zone_id],
              second_route[movement_.second_route_zone_id]);
    best_neighbor->UpdateRouteTime(movement_.first_vehicle_id, instance);
    best_neighbor->UpdateRouteTime(movement_.second_vehicle_id, instance);
    return {true, best_neighbor};
  }
  return {false, solution};
}

InterSwapTimes InterSwap::GetNewTime(SolutionPtr solution,
                                     InterSwapMovement movement,
                                     std::shared_ptr<VRPInstance> instance) {
  InterSwapTimes times;
  times.movement = movement;
  double old_time = solution->total_time();
  std::vector<ZonePtr> first_route =
      solution->vehicles()[movement.first_vehicle_id - 1]->route();
  std::vector<ZonePtr> second_route =
      solution->vehicles()[movement.second_vehicle_id - 1]->route();
  times.first_route_time =
      solution->vehicles()[movement.first_vehicle_id - 1]->TimeUsed();
  times.second_route_time =
      solution->vehicles()[movement.second_vehicle_id - 1]->TimeUsed();
  ZonePtr zone_1 = first_route[movement.first_route_zone_id];
  ZonePtr zone_2 = second_route[movement.second_route_zone_id];
  ZonePtr parent_zone_1 = first_route[movement.first_route_zone_id - 1];
  ZonePtr child_zone_1 = first_route[movement.first_route_zone_id + 1];
  ZonePtr parent_zone_2 = second_route[movement.second_route_zone_id - 1];
  ZonePtr child_zone_2 = second_route[movement.second_route_zone_id + 1];
  // Substracted
  double first_parent =
      instance->CalculateTime(parent_zone_1->id(), zone_1->id());
  double first_child =
      instance->CalculateTime(zone_1->id(), child_zone_1->id());
  times.first_route_time -= (first_parent + first_child);
  times.first_route_time -= zone_1->process_time();
  double second_parent =
      instance->CalculateTime(parent_zone_2->id(), zone_2->id());
  double second_child =
      instance->CalculateTime(zone_2->id(), child_zone_2->id());
  times.second_route_time -= (second_parent + second_child);
  times.second_route_time -= zone_2->process_time();
  double deleted_time =
      first_parent + first_child + second_parent + second_child;
  // std::cout << "Quitamos " << parent_zone_1->id() << " " << zone_1->id() <<
  // "Costo: " << first_parent << std::endl; std::cout << "Quitamos " <<
  // zone_1->id() << " " << child_zone_1->id() <<" Costo: " << first_child <<
  // std::endl; std::cout << "Quitamos " << parent_zone_2->id() << " " <<
  // zone_2->id() <<" Costo: " << second_parent<< std::endl; std::cout <<
  // "Quitamos " << zone_2->id() << " " << child_zone_2->id() <<" Costo: " <<
  // second_child << std::endl;
  // Added
  first_parent = instance->CalculateTime(parent_zone_1->id(), zone_2->id());
  first_child = instance->CalculateTime(zone_2->id(), child_zone_1->id());
  times.first_route_time += (first_parent + first_child);
  times.first_route_time += zone_2->process_time();
  second_parent = instance->CalculateTime(parent_zone_2->id(), zone_1->id());
  second_child = instance->CalculateTime(zone_1->id(), child_zone_2->id());
  times.second_route_time += (second_parent + second_child);
  times.second_route_time += zone_1->process_time();
  double added_time = first_parent + first_child + second_parent + second_child;
  // std::cout << "Agreg " << parent_zone_1->id() << " " << zone_2->id() << "
  // Costo: " << first_parent << std::endl; std::cout << "Agreg " <<
  // zone_2->id() << " " << child_zone_1->id() << " Costo: " << first_child <<
  // std::endl; std::cout << "Agreg " << parent_zone_2->id() << " " <<
  // zone_1->id() << " Costo: " << second_parent << std::endl; std::cout <<
  // "Agreg " << zone_1->id() << " " << child_zone_2->id() << " Costo: " <<
  // second_child << std::endl; std::cout <<  "RESULT " << old_time -
  // deleted_time + added_time << std::endl;
  times.whole_time = old_time - deleted_time + added_time;
  return times;
}

bool InterSwap::IsLegalMovement(SolutionPtr solution, InterSwapTimes times,
                                std::shared_ptr<VRPInstance> instance) {
  if (times.first_route_time > instance->max_collection_time() ||
      times.second_route_time > instance->max_collection_time()) {
    return false;
  }
  InterSwapMovement candidate = times.movement;
  auto first_route =
      solution->vehicles()[candidate.first_vehicle_id - 1]->route();
  auto second_route =
      solution->vehicles()[candidate.second_vehicle_id - 1]->route();
  std::swap(first_route[candidate.first_route_zone_id],
            second_route[candidate.second_route_zone_id]);
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
  return true;
}