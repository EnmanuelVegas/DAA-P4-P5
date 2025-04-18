/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @file inter_swap.h
 * @brief Declaration of the `InterSwap` class and related structures.
 *
 * This file contains the definition of the `InterSwap` class, which implements
 * a local search method for swapping zones between routes in the context of the
 * Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef INTER_SWAP_H
#define INTER_SWAP_H

#include "local_search.h"

/**
 * @struct InterSwapMovement
 * @brief Represents a swap movement between routes.
 *
 * Contains the identifiers of the vehicles and zones involved in the movement.
 */
struct InterSwapMovement {
  int first_vehicle_id = -1;
  int second_vehicle_id = -1;
  int first_route_zone_id = -1;
  int second_route_zone_id = -1;
};

/**
 * @struct InterSwapTimes
 * @brief Represents the times associated with a swap movement.
 *
 * Contains the total and partial times of the routes affected by the movement.
 */
struct InterSwapTimes {
  InterSwapMovement movement = InterSwapMovement();
  double whole_time = -1;
  double first_route_time = -1;
  double second_route_time = -1;
};

/**
 * @class InterSwap
 * @brief Implements a local search method for swapping zones between routes.
 *
 * The `InterSwap` class inherits from `LocalSearch` and provides methods to
 * find the best neighbor using swap movements.
 */
class InterSwap : public LocalSearch {
 public:
  /**
   * @brief Default constructor.
   */
  InterSwap() : movement_(InterSwapMovement()) {}

  /**
   * @brief Default destructor.
   */
  ~InterSwap() {}

  /**
   * @brief Finds the best neighbor using swap movements.
   *
   * @param solution Current solution.
   * @param instance VRP problem instance.
   * @return A pair indicating whether a better neighbor was found and the
   * corresponding solution.
   */
  std::pair<bool, SolutionPtr> GetBestNeighbor(
      SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  /**
   * @brief Returns the type of local search.
   *
   * @return A string describing the type of local search.
   */
  std::string type() { return "Inter swap.\n"; }

 private:
  /**
   * @brief Calculates the new times associated with a swap movement.
   *
   * @param solution Current solution.
   * @param movement Swap movement.
   * @param instance VRP problem instance.
   * @return The times associated with the movement.
   */
  InterSwapTimes GetNewTime(SolutionPtr solution, InterSwapMovement movement,
                            std::shared_ptr<VRPInstance> instance);

  /**
   * @brief Verifies if a swap movement is valid.
   *
   * @param solution Current solution.
   * @param times Times associated with the movement.
   * @param instance VRP problem instance.
   * @return true if the movement is valid, false otherwise.
   */
  bool IsLegalMovement(SolutionPtr solution, InterSwapTimes times,
                       std::shared_ptr<VRPInstance> instance);

  InterSwapMovement movement_;
};

#endif