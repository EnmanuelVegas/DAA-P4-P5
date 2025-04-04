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

std::pair<bool, SolutionPtr> InterReinsertion::Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  for (auto& vehicle : solution->vehicles()) {
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) {
      for (int j{1}; j < route_size - 1; j++) {
        if (i == j) {
          continue;
        }
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);
        auto& route = new_solution->vehicles()[vehicle->id() - 1]->route();
        ZonePtr zone = route[i];
        route.erase(route.begin() + i);
        route.insert(route.begin() + j, zone);
        // if (IsFeasible(new_solution, i, j, vehicle, instance)) {
        if (solution->IsRouteFeasible(vehicle->id(), instance)) {
          if (new_solution->total_time() < solution->total_time()) {
            return {true, solution};
          }
        }
      }
    }
  }
  return {false, solution};
}

bool InterReinsertion::IsFeasible(SolutionPtr solution, int extraction_index, int insertion_index, VehiclePtr vehicle, std::shared_ptr<VRPInstance> instance) {
  // if (Verificar capacidad)
  // double route_time = solution->total_time();
  // ZonePtr inserted = vehicle->route()[insertion_index];
  // ZonePtr old_parent = vehicle->route()[extraction_index - 1];
  // ZonePtr old_child = vehicle->route()[extraction_index];
  // ZonePtr new_parent = vehicle->route()[insertion_index - 1];
  // ZonePtr new_child = vehicle->route()[insertion_index + 1];
  // // Adjust the extraction
  // route_time -= instance->CalculateTime(old_parent->id(), inserted->id());
  // route_time -= instance->CalculateTime(inserted->id(), old_child->id());
  // route_time += instance->CalculateTime(old_parent->id(), old_child->id());
  // // Adjust the insertion
  // route_time -= instance->CalculateTime(old_parent->id(), old_child->id());
  // route_time += instance->CalculateTime(new_parent->id(), inserted->id());
  // route_time += instance->CalculateTime(inserted->id(), new_child->id());
  return true;
}

