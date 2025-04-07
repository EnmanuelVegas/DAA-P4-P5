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
  // std::cout << solution->total_time() << std::endl;
  int contador{1};
  SolutionPtr local_optimal = std::make_shared<Solution>(*solution);
  for (auto& vehicle : solution->vehicles()) {
    // std::cout << "Vehicle " << vehicle->id() << " con " << vehicle->route().size()<< " zonas"<< std::endl;
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) { // From 1 to route size - 2 to avoid mixing the depots
      for (int j{1}; j < route_size - 1; j++) {
        if ((instance->IsTransferStation(vehicle->route()[i])) || 
            (instance->IsTransferStation(vehicle->route()[j])) || 
            i == j) {
          continue;
        }
        // std::cout << "Movimiento " << i << " " << j << "\n";
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);
        auto& route = new_solution->vehicles()[vehicle->id() - 1]->route();
        // new_solution->PrintVehicleRoute(vehicle->id());
        std::swap(route[i], route[j]);
        // new_solution->PrintVehicleRoute(vehicle->id());
        if (new_solution->IsRouteFeasible(vehicle->id(), instance)) {
          // std::cout << new_solution->total_time() << " " << local_optimal->total_time() << std::endl;
          if (new_solution->total_time() < local_optimal->total_time()) {
            // std::cout << contador++ <<  ": " << new_solution->total_time() << std::endl;
            local_optimal = new_solution;
            local_optimal->improvements_counter() = local_optimal->improvements_counter() + 1;
          }
        }
      }
    }
  }
  if (local_optimal->total_time() < solution->total_time()) {
    return {true, local_optimal};
  }
  return {false, solution};
}