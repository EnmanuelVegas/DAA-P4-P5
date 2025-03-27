/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.h: Declaracion de la clase 'GreedyVehicleRoute'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef VRPT_H
#define VRPT_H

#include <fstream>
#include <vector>
#include <set>

#include "vrp_instance.h"
#include "greedy_vehicle_route.h"

/*
 * VRPT stands for Vehicle Routing Problem.
*/
class VRPTransshipments {
 public:
  VRPTransshipments(std::shared_ptr<VRPInstance> instance);

  // std::vector<Vehicle> ComputeUsedVehicles();
  
  std::vector<Vehicle> ComputeRoutes();
  
 private:
  std::shared_ptr<VRPInstance> instance_;
  GreedyVehicleRoute route_generator_;
  std::vector<Zone> zones_;
  std::vector<Zone> transport_zones_;
};

#endif