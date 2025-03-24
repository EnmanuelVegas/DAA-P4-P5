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

#include "greedy_vehicle_route.h"

/*
 * VRPT stands for Vehicle Routing Problem.
*/
class VRPTransshipments {
 public:
  VRPTransshipments() : route_generator_(GreedyVehicleRoute()) { }

  std::vector<Vehicle> ComputeUsedVehicles();
  
  // std::vector<Route> SolveAlgorithm(std::vector<Zone> collection_zones);
  
 private:
  GreedyVehicleRoute route_generator_;
  std::vector<Zone> zones_;
  int collection_capacity_;
  int max_time_;
  std::vector<Zone> transport_zones_;
  Zone depot_;
  // std::vector<Route> completed_routes_;

};

#endif