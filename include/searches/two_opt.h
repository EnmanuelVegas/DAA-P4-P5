/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file two_opt.h
 *
 * This file contains the definition of the `TwoOpt` class, which implements
 * the 2-opt local search method for route optimization in the context of the
 * Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef TWO_OPT_H
#define TWO_OPT_H

#include "local_search.h"

/**
 * @struct TwoOptMovement
 * @brief Represents a 2-opt movement within a route.
 *
 * Contains the vehicle ID and the positions involved in the movement.
 */
struct TwoOptMovement {
  int vehicle_id = -1;
  int delete_pos = -1;
  int insert_pos = -1;
};

/**
 * @class TwoOpt
 * @brief Implements the 2-opt local search method.
 *
 * The `TwoOpt` class inherits from `LocalSearch` and provides methods to find
 * the best neighbor using 2-opt movements.
 */
class TwoOpt : public LocalSearch {
 public:
  /**
   * @brief Default constructor.
   */
  TwoOpt() : movement_(TwoOptMovement()) {}

  /**
   * @brief Default destructor.
   */
  ~TwoOpt() {}

  /**
   * @brief Finds the best neighbor using 2-opt.
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
  std::string type() { return "2-opt.\n"; }

 private:
  /**
   * @brief Verifies if a 2-opt movement is valid.
   *
   * @param solution Current solution.
   * @param movement 2-opt movement.
   * @param instance VRP problem instance.
   * @return true if the movement is valid, false otherwise.
   */
  // bool IsLegalMovement(SolutionPtr solution, TwoOptMovement movement,
  //                      std::shared_ptr<VRPInstance> instance);

  TwoOptMovement movement_;
};

#endif