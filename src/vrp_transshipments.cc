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

std::vector<Vehicle> VRPTransshipments::ComputeUsedVehicles() {
  return route_generator_.SolveAlgorithm(zones_, collection_capacity_, max_time_, transport_zones_, depot_);
}
