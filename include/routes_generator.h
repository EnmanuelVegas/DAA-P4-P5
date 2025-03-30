/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef GREEDY_VEHICLE_ROUTE_H
#define GREEDY_VEHICLE_ROUTE_H

#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>

#include "./tools/utils.h"
#include "route.h"
#include "vehicle.h"
#include "vrp_instance.h"
#include "zone.h"

class RoutesGenerator {
 public:
  RoutesGenerator(std::shared_ptr<VRPInstance> instance, int candidate_size)
      : candidates_size_(candidate_size), instance_(instance) {}

  std::vector<VehiclePtr> Generate();

  // std::vector<VehiclePtr> SolveGRASP();

  double CalculateTime(ZonePtr actual, int destination_id);

  double ReturnToDepotTime(ZonePtr actual_zone, int closest_id);

  ZonePtr SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates);

  ZonePtr SelectRandomizedClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates);

  ZonePtr SelectClosestTransferStation(int zone_id);

  bool BelongsTo(ZonePtr zone, ZonePtrPair& zones);

 private:
  std::shared_ptr<VRPInstance> instance_;
  int candidates_size_;
  std::vector<VehiclePtr> vehicles_used_;
};

#endif