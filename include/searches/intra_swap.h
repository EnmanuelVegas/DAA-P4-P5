/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file intra_swap.h
 * @brief Declaration of the `IntraSwap` class and related structures.
 *
 * This file contains the definition of the `IntraSwap` class, which implements
 * a local search method for swapping zones within the same route in the context
 * of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef INTRA_SWAP_H
#define INTRA_SWAP_H

#include "local_search.h"

/**
 * @struct IntraSwapMovement
 * @brief Represents a swap movement within a route.
 *
 * Contains the vehicle ID and the positions involved in the movement.
 */
struct IntraSwapMovement {
  int vehicle_id = -1;
  int first_zone_id = -1;
  int second_zone_id = -1;
};

/**
 * @class IntraSwap
 * @brief Implements a local search method for swapping zones within a route.
 *
 * The `IntraSwap` class inherits from `LocalSearch` and provides methods
 * to find the best neighbor using swap movements.
 */
class IntraSwap : public LocalSearch {
 public:
  /**
   * @brief Default constructor.
   */
  IntraSwap() : movement_(IntraSwapMovement()) {}

  /**
   * @brief Default destructor.
   */
  ~IntraSwap() {}

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
  std::string type() { return "Intra swap.\n"; }

 private:
  /**
   * @brief Calculates the new times associated with a swap movement.
   *
   * @param solution Current solution.
   * @param movement Swap movement.
   * @param instance VRP problem instance.
   * @return The times associated with the movement.
   */
  double GetNewTime(SolutionPtr solution, IntraSwapMovement movement,
                    std::shared_ptr<VRPInstance> instance);

  /**
   * @brief Verifies if a swap movement is valid.
   *
   * @param solution Current solution.
   * @param movement Swap movement.
   * @param instance VRP problem instance.
   * @return true if the movement is valid, false otherwise.
   */
  bool IsLegalMovement(SolutionPtr solution, IntraSwapMovement movement,
                       std::shared_ptr<VRPInstance> instance);

  IntraSwapMovement movement_;
};

#endif