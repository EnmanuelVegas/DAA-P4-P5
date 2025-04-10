/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/intra_swap.h"

std::pair<bool, SolutionPtr> IntraSwap::GetLocalOptimum(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  SolutionPtr local_optimal = std::make_shared<Solution>(*solution);
  for (auto& vehicle : solution->vehicles()) {
    // std::cout << "Vehicle " << vehicle->id() << " con " << vehicle->route().size()<< " zonas"<< std::endl;
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) { // From 1 to route size - 2 to avoid mixing the depots
      for (int j{i + 1}; j < route_size - 1; j++) {
        if ((instance->IsTransferStation(vehicle->route()[i])) || 
            (instance->IsTransferStation(vehicle->route()[j])) || 
            i == j) {
          continue;
        }
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);
        double new_time = GetNewTime(new_solution, vehicle->id(), i, j, instance);
        if (!(new_time < local_optimal->total_time())) {
          continue;
        }
        auto& route = new_solution->vehicles()[vehicle->id() - 1]->route();
        // new_solution->PrintVehicleRoute(vehicle->id());
        std::swap(route[i], route[j]);
        // new_solution->PrintVehicleRoute(vehicle->id());
        if (new_solution->IsRouteFeasible(vehicle->id(), instance)) {
          new_solution->UpdateTotalTime(new_time);
          local_optimal = new_solution;
        }
      }
    }
  }
  if (local_optimal->total_time() < solution->total_time()) {
    return {true, local_optimal};
  }
  return {false, solution};
}

double IntraSwap::GetNewTime(SolutionPtr new_solution, int vehicle_id, int zone_1_pos, int zone_2_pos, std::shared_ptr<VRPInstance> instance) {
  double old_time = new_solution->total_time();
  std::vector<ZonePtr> route = new_solution->vehicles()[vehicle_id - 1]->route();
  ZonePtr zone_1 = route[zone_1_pos];
  ZonePtr zone_2 = route[zone_2_pos];
  ZonePtr parent_zone_1 = route[zone_1_pos - 1];
  ZonePtr child_zone_1 = route[zone_1_pos + 1];
  ZonePtr parent_zone_2 = route[zone_2_pos - 1];
  ZonePtr child_zone_2 = route[zone_2_pos + 1];
  // Substracted
  double first_parent = instance->CalculateTime(parent_zone_1->id(), zone_1->id());
  double first_child = instance->CalculateTime(zone_1->id(), child_zone_1->id());
  double second_parent = instance->CalculateTime(parent_zone_2->id(), zone_2->id());
  double second_child = instance->CalculateTime(zone_2->id(), child_zone_2->id());
  double deleted_time = first_parent + first_child + second_parent + second_child;
  // std::cout << "Quitamos " << parent_zone_1->id() << " " << zone_1->id() << std::endl;
  // std::cout << "Quitamos " << zone_1->id() << " " << child_zone_1->id() << std::endl;
  // std::cout << "Quitamos " << parent_zone_2->id() << " " << zone_2->id() << std::endl;
  // std::cout << "Quitamos " << zone_2->id() << " " << child_zone_2->id() << std::endl;
  // Added
  first_parent = instance->CalculateTime(parent_zone_1->id(), zone_2->id());
  // std::cout << "Agreg " << parent_zone_1->id() << " " << zone_2->id() << std::endl;
  if (std::abs(zone_1_pos - zone_2_pos) == 1) {
    // std::cout << "Agreg " << zone_2->id() << " " << zone_1->id() << std::endl;
    // std::cout << "Agreg " << zone_2->id() << " " << zone_1->id() << std::endl;
    first_child = instance->CalculateTime(zone_2->id(), zone_1->id());
    second_parent = instance->CalculateTime(zone_1->id(), zone_2->id());  
  }
  else {
    // std::cout << "Agreg " << zone_2->id() << " " << child_zone_1->id() << std::endl;
    // std::cout << "Agreg " << parent_zone_2->id() << " " << zone_1->id() << std::endl;
    first_child = instance->CalculateTime(zone_2->id(), child_zone_1->id());
    second_parent = instance->CalculateTime(parent_zone_2->id(), zone_1->id());
  }
  // std::cout << "Agreg " << zone_1->id() << " " << child_zone_2->id() << std::endl;
  second_child = instance->CalculateTime(zone_1->id(), child_zone_2->id());
  double added_time = first_parent + first_child + second_parent + second_child;

  // std::cout << "TIME DIFF FUERA: " << added_time - deleted_time << std::endl;
  new_solution->vehicles()[vehicle_id - 1]->UpdateRouteTime(added_time - deleted_time);

  // std::cout <<  "RESULT " << old_time - deleted_time + added_time << std::endl;
  return old_time - deleted_time + added_time;
}
