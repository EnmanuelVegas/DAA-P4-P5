/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.h: Declaracion de la clase 'GreedyVehicleRoute'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef GREEDY_VEHICLE_ROUTE_H
#define GREEDY_VEHICLE_ROUTE_H

#include <fstream>
#include <vector>
#include <memory>

#include "route.h"
#include "zone.h"
#include "vehicle.h"
#include "vrp_instance.h"
#include "./tools/utils.h"

class GreedyVehicleRoute {
 public:
  GreedyVehicleRoute() { }

  std::vector<Vehicle> SolveAlgorithm(std::shared_ptr<VRPInstance> instance);

  std::shared_ptr<CollectionZone> SelectClosestZone(
    std::shared_ptr<VRPInstance> zone,
    std::vector<std::shared_ptr<Zone>>& candidates);

  bool BelongsTo(Zone zone, std::vector<Zone>& candidates);



 private:
  std::vector<Vehicle> vehicles_used_;
};

#endif