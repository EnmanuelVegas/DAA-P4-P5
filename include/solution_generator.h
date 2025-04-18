/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file solution_generator.h: Declaracion de la clase 'SolutionGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef GREEDY_VEHICLE_ROUTE_H
#define GREEDY_VEHICLE_ROUTE_H

#include <algorithm>
#include <algorithm>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include "./searches/inter_reinsertion.h"
#include "./searches/inter_swap.h"
#include "./searches/intra_reinsertion.h"
#include "./searches/intra_swap.h"
#include "./searches/search_method_selector.h"
#include "./tools/utils.h"
#include "solution.h"
#include "vrp_instance.h"

class SolutionGenerator {
 public:
  SolutionGenerator(std::shared_ptr<VRPInstance> instance, int candidate_size,
                    int multistart_rep, int seed = std::random_device{}())
      : candidates_size_(candidate_size),
        multistart_rep_(multistart_rep),
        instance_(instance),
        gen_(seed),
        search_selector_(seed) {}

  SolutionPtr GenerateSolution();

  double CalculateRoutesTime(SolutionPtr vehicles);

  double ReturnToDepotTime(ZonePtr actual_zone, ZonePtr closest);

  ZonePtr SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates);

  ZonePtr SelectClosestTransferStation(int zone_id);

  void AddNormalStop(ZonePtr last, ZonePtr closest,
                     CollectionVehiclePtr vehicle);

  void AddTransferStop(ZonePtr last, ZonePtr transfer,
                       CollectionVehiclePtr vehicle, double capacity,
                       double max_time);

  // void PrintTable();

 private:
  SolutionPtr BuildCollectionRoutes();

  SolutionPtr BuildTransferRoutes(SolutionPtr solution);

  SolutionPtr RandomVND(SolutionPtr solution);

  std::shared_ptr<VRPInstance> instance_;
  Solution final_solution_;
  SearchMethodSelector search_selector_;
  std::mt19937 gen_;
  int candidates_size_;
  int multistart_rep_;
};

#endif