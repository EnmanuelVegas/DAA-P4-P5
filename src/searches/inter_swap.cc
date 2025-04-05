/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/inter_swap.h"

std::pair<bool, SolutionPtr> InterSwap::Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  // std::cout << solution->total_time() << std::endl;
  for (auto& vehicle : solution->vehicles()) {
    // std::cout << "Vehicle " << vehicle->id() << " con " << vehicle->route().size()<< " zonas"<< std::endl;
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) { // From 1 to route size - 2 to avoid mixing the depots
      for (auto& other_vehicle : solution->vehicles()) {
        if (other_vehicle == vehicle) {
          continue;
        }
        int other_route_size{int(other_vehicle->route().size())};
        for (int j{1}; j < other_route_size - 1; j++) { // From 1 to route size - 2 to avoid mixing the depots  
          // std::cout << "Movimiento " << i << " " << j << "\n";
          SolutionPtr new_solution = std::make_shared<Solution>(*solution);
          auto& first_route = new_solution->vehicles()[vehicle->id() - 1]->route();
          auto& second_route = new_solution->vehicles()[other_vehicle->id() - 1]->route();
          // ZonePtr zone = route[i];
          // for (auto& zone : new_solution->vehicles()[vehicle->id() - 1]->route()) {
          //   std::cout << zone->id() << " ";
          // }
          // std::cout << std::endl;
          std::swap(first_route[i], second_route[j]);
          // for (auto& zone : new_solution->vehicles()[vehicle->id() - 1]->route()) {
          //   std::cout << zone->id() << " ";
          // }
          // std::cout << std::endl;
          if (new_solution->IsRouteFeasible(vehicle->id(), instance) &&
              new_solution->IsRouteFeasible(other_vehicle->id(), instance)) {
            // std::cout << new_solution->total_time() << " " << solution->total_time() << std::endl;
            if (new_solution->total_time() < solution->total_time()) {
              return {true, new_solution};
            }
          }
        }
      }
    }
  }
  // std::cout << solution->total_time() << std::endl;
  return {false, solution};
}