/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.cc: Definición de métodos de la clase
 * 'VRPTransshipments'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/vrp_transshipments.h"

VRPTransshipments::VRPTransshipments(std::shared_ptr<VRPInstance> instance,
                                     int candidates_size,
                                     int multistart_quantity, int seed)
    : instance_(instance),
      route_generator_(SolutionGenerator(instance, candidates_size, seed)) {
  return;
}

SolutionPtr VRPTransshipments::ComputeRoutes() {
  SolutionPtr problem_solution = route_generator_.GenerateSolution();
  return problem_solution;
}
