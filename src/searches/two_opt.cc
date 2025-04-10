/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/two_opt.h"

std::pair<bool, SolutionPtr> TwoOpt::Apply(
    SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  SolutionPtr local_optimal = std::make_shared<Solution>(*solution);
  bool improved = false;

  for (auto& vehicle : solution->vehicles()) {
    auto& route = vehicle->route();
    int route_size = int(route.size());

    for (int i = 1; i < route_size - 2; i++) {  // Evitar los depósitos
      for (int j = i + 1; j < route_size - 1; j++) {  // j siempre debe ser mayor que i
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);
        auto& new_route = new_solution->vehicles()[vehicle->id() - 1]->route();
        std::reverse(new_route.begin() + i, new_route.begin() + j + 1);
        if (new_solution->IsRouteFeasible(vehicle->id(), instance)) {
          if (new_solution->total_time() < local_optimal->total_time()) {
            local_optimal = new_solution;
            improved = true;
          }
        }
      }
    }
  }

  return {improved, local_optimal};
}