/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file solution_generator.h
 * @brief Declaration of the `SolutionGenerator` class.
 *
 * This file contains the definition of the `SolutionGenerator` class, which
 * is responsible for generating solutions for the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

 #ifndef SOLUTION_GENERATOR_ROUTE_H
 #define SOLUTION_GENERATOR_ROUTE_H
 
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
#include "./tools/timer.h"
#include "solution.h"
#include "vrp_instance.h"
 
/**
* @class SolutionGenerator
* @brief Generates solutions for the Vehicle Routing Problem (VRP).
*
* The `SolutionGenerator` class provides methods to construct and optimize
* solutions for the VRP using various local search techniques.
*/
class SolutionGenerator {
public:
  /**
  * @brief Constructor for `SolutionGenerator`.
  *
  * Initializes the solution generator with the given VRP instance, candidate size,
  * multistart repetitions, and random seed.
  *
  * @param instance A shared pointer to the VRP instance.
  * @param candidate_size The size of the candidate list.
  * @param multistart_rep The number of multistart repetitions.
  * @param seed The random seed (default is a random device).
  */
  SolutionGenerator(std::shared_ptr<VRPInstance> instance, int candidate_size,
  int multistart_rep, int seed = std::random_device{}())
    : candidates_size_(candidate_size),
      multistart_rep_(multistart_rep),
      instance_(instance),
      gen_(seed),
      search_selector_(seed) { }

  /**
  * @brief Generates a solution for the VRP.
  *
  * Constructs a solution by building collection and transfer routes and applying
  * optimization techniques.
  *
  * @return A pointer to the generated solution.
  */
  SolutionPtr GenerateSolution();

  /**
  * @brief Calculates the time required to return to the depot.
  *
  * @param actual_zone The current zone.
  * @param closest The closest zone to the depot.
  * @return The time required to return to the depot.
  */
  double ReturnToDepotTime(ZonePtr actual_zone, ZonePtr closest);

  /**
  * @brief Selects the closest zone to the given zone.
  *
  * @param zone The current zone.
  * @param candidates A vector of candidate zones.
  * @return The closest zone from the candidates.
  */
  ZonePtr SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates);

  /**
  * @brief Selects the closest transfer station to the given zone.
  *
  * @param zone_id The ID of the current zone.
  * @return The closest transfer station.
  */
  ZonePtr SelectClosestTransferStation(int zone_id);

  /**
  * @brief Adds a normal stop to the route of a collection vehicle.
  *
  * @param last The last zone in the route.
  * @param closest The closest zone to add.
  * @param vehicle The collection vehicle.
  */
  void AddNormalStop(ZonePtr last, ZonePtr closest,
                    CollectionVehiclePtr vehicle);

  /**
  * @brief Adds a transfer stop to the route of a collection vehicle.
  *
  * @param last The last zone in the route.
  * @param transfer The transfer station to add.
  * @param vehicle The collection vehicle.
  * @param capacity The capacity of the vehicle.
  * @param max_time The maximum time allowed for the route.
  */
  void AddTransferStop(ZonePtr last, ZonePtr transfer,
                      CollectionVehiclePtr vehicle, double capacity,
                      double max_time);

private:
  /**
  * @brief Builds the collection routes for the solution.
  *
  * Constructs the routes for the collection vehicles.
  *
  * @return A pointer to the solution containing the collection routes.
  */
  SolutionPtr BuildCollectionRoutes();

  /**
  * @brief Builds the transfer routes for the solution.
  *
  * Constructs the routes for the transfer vehicles.
  *
  * @param solution The solution containing the collection routes.
  * @return A pointer to the solution containing the transfer routes.
  */
  SolutionPtr BuildTransferRoutes(SolutionPtr solution);

  /**
  * @brief Applies the Random Variable Neighborhood Descent (VND) algorithm.
  *
  * Optimizes the solution using the Random VND algorithm.
  *
  * @param solution The initial solution.
  * @return A pointer to the optimized solution.
  */
  SolutionPtr RandomVND(SolutionPtr solution);

  std::shared_ptr<VRPInstance> instance_;
  Solution final_solution_;
  SearchMethodSelector search_selector_;
  std::mt19937 gen_;
  int candidates_size_;
  int multistart_rep_;
};

#endif