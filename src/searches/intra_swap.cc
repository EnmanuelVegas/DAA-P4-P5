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

std::pair<bool, SolutionPtr> IntraSwap::Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  // std::cout << "INTRA" << std::endl;
  // std::cout << solution->total_time() << std::endl;
  for (auto& vehicle : solution->vehicles()) {
    // std::cout << "Vehicle " << vehicle->id() << " con " << vehicle->route().size()<< " zonas"<< std::endl;
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) { // From 1 to route size - 2 to avoid mixing the depots
      for (int j{1}; j < route_size - 1; j++) {
        if (i == j) {
          continue;
        }
        std::cout << "Movimiento " << i << " " << j << "\n";
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);
        auto& route = new_solution->vehicles()[vehicle->id() - 1]->route();
        // ZonePtr zone = route[i];
        // for (auto& zone : new_solution->vehicles()[vehicle->id() - 1]->route()) {
        //   std::cout << zone->id() << " ";
        // }
        // std::cout << std::endl;
        std::swap(route[i], route[j]);
        // for (auto& zone : new_solution->vehicles()[vehicle->id() - 1]->route()) {
        //   std::cout << zone->id() << " ";
        // }
        std::cout << new_solution->total_time() << std::endl;

        // std::cout << std::endl;
        if (new_solution->IsRouteFeasible(vehicle->id(), instance)) {
          std::cout << new_solution->total_time() << std::endl;
          // std::cout << new_solution->total_time() << " " << solution->total_time() << std::endl;
          if (new_solution->total_time() < solution->total_time()) {
            return {true, new_solution};
          }
        }
      }
    }
  }
  std::cout << solution->total_time() << std::endl;
  return {false, solution};
}