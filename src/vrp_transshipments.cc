/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.cc: Definición de métodos de la clase 'VRPTransshipments'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/vrp_transshipments.h"

VRPTransshipments::VRPTransshipments(std::shared_ptr<VRPInstance> instance) 
  : instance_(instance), route_generator_(GreedyVehicleRoute()) {
    return;
}


std::vector<VehiclePtr> VRPTransshipments::ComputeRoutes() {
  return route_generator_.SolveAlgorithm(this->instance_);
}
