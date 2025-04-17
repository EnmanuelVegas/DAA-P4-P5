/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file solution_generator.h: Declaracion de la clase 'SolutionGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef VRPT_H
#define VRPT_H

#include <fstream>
#include <set>
#include <vector>

#include "solution_generator.h"
#include "vrp_instance.h"

/*
 * VRPT stands for Vehicle Routing Problem.
 */
class VRPTransshipments {
 public:
  VRPTransshipments(std::shared_ptr<VRPInstance> instance, int candidates_size,
                    int multistart_quantity, int seed = std::random_device{}());

  // std::vector<Vehicle> ComputeUsedVehicles();

  SolutionPtr ComputeRoutes();

 private:
  std::shared_ptr<VRPInstance> instance_;
  SolutionGenerator route_generator_;
  std::vector<Zone> zones_;
  std::vector<Zone> transport_zones_;
};

#endif