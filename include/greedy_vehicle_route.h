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
#include <algorithm>

#include "route.h"
#include "zone.h"
#include "vehicle.h"
#include "vrp_instance.h"
#include "./tools/utils.h"

class GreedyVehicleRoute {
 public:
  GreedyVehicleRoute(std::shared_ptr<VRPInstance> instance) : instance_(instance) { }

  std::vector<VehiclePtr> SolveAlgorithm();

  double CalculateTime(ZonePtr actual, int destination_id);

  double ReturnToDepotTime(ZonePtr actual_zone, int closest_id);

  ZonePtr SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates);

  ZonePtr SelectClosestTransferStation(int zone_id);

  bool BelongsTo(ZonePtr zone, ZonePtrPair& zones);


 private:
  std::shared_ptr<VRPInstance> instance_;
  std::vector<VehiclePtr> vehicles_used_;
};

#endif