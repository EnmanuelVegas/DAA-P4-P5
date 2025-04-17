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

std::pair<bool, SolutionPtr> TwoOpt::GetBestNeighbor(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  std::cout << *solution;
  SolutionPtr best_neighbor = std::make_shared<Solution>(*solution);
  for (auto& vehicle : solution->vehicles()) {
    auto& route = vehicle->route();
    int route_size = int(route.size());
    for (int i = 1; i < route_size - 1; i++) {
      for (int j = i + 1; j < route_size - 1; j++) {
        if ((instance->IsTransferStation(vehicle->route()[i])) ||
            (instance->IsTransferStation(vehicle->route()[j]))) {
          continue;
        }
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);
        auto& new_route = new_solution->vehicles()[vehicle->id() - 1]->route();
        std::cout << "Unimos en la ruta " << vehicle->id() << " a " << new_route[i]->id() << " con " << new_route[j]->id() << std::endl;
        std::reverse(new_route.begin() + i, new_route.begin() + j + 1);
        if (new_solution->IsRouteFeasible(vehicle->id(), instance)) {
          if (IsLess(new_solution->total_time(), best_neighbor->total_time())) {
            std::cout << "MEJORISIMA" << std::endl;
            best_neighbor = new_solution;
          }
        }
      }
    }
  }
  if (IsLess(best_neighbor->total_time(), solution->total_time())) {
    std::cout << *best_neighbor;
    return {true, best_neighbor};
  }
  return {false, solution};
}