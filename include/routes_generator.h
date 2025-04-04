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
#include <limits>
#include <algorithm>  // Para std::sort
#include <random>     // Para generar números aleatorios

#include "./tools/utils.h"
#include "vrp_instance.h"
#include "solution.h"
#include "./searches/inter_reinsertion.h"

class RoutesGenerator {
 public:
  RoutesGenerator(std::shared_ptr<VRPInstance> instance, int candidate_size, int seed = std::random_device{}())
      : candidates_size_(candidate_size), instance_(instance), gen_(seed) {}

  SolutionPtr GenerateGRASP();

  SolutionPtr PerformLocalSearch(SolutionPtr solution);

  double CalculateTime(int actual_id, int destination_id);

  double CalculateRoutesTime(SolutionPtr vehicles);

  double ReturnToDepotTime(ZonePtr actual_zone, ZonePtr closest);

  ZonePtr SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates);

  ZonePtr SelectClosestTransferStation(int zone_id);

  bool BelongsTo(ZonePtr zone, ZonePtrPair& zones);

  void AddNormalStop(ZonePtr last, ZonePtr closest, VehiclePtr vehicle);

  void AddTransferStop(ZonePtr last, ZonePtr transfer, VehiclePtr vehicle, double capacity, double max_time);

  // void PrintTable();

 private:
  SolutionPtr GenerateSingleRoute();
  std::shared_ptr<VRPInstance> instance_;
  std::mt19937 gen_;  
  int candidates_size_;
};

#endif