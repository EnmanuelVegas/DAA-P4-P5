/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file inter_reinsertion.h
 *
 * This file contains the definition of the `InterReinsertion` class, which
 * implements a local search method to solve reinsertion problems between routes
 * in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef INTER_REINSERTION_H
#define INTER_REINSERTION_H

#include "local_search.h"

/**
 * @struct InterReinsertionMovement
 * @brief Represents a reinsertion movement between routes.
 *
 * Contains the identifiers of the vehicles and zones involved in the movement.
 */
struct InterReinsertionMovement {
  int delete_vehicle_id = -1;
  int insert_vehicle_id = -1;
  int delete_zone_id = -1;
  int insert_zone_id = -1;
};

/**
 * @struct InterReinsertionTimes
 * @brief Represents the times associated with a reinsertion movement.
 *
 * Contains the total and partial times of the routes affected by the movement.
 */
struct InterReinsertionTimes {
  InterReinsertionMovement movement = InterReinsertionMovement();
  double whole_time = -1;
  double delete_route_time = -1;
  double insert_route_time = -1;
};

/**
 * @class InterReinsertion
 * @brief Implements a local search method for reinsertion between routes.
 *
 * The `InterReinsertion` class inherits from `LocalSearch` and provides methods
 * to find the best neighbor using reinsertion movements.
 */
class InterReinsertion : public LocalSearch {
 public:
  /**
   * @brief Default constructor.
   */
  InterReinsertion() : movement_(InterReinsertionMovement()) {}

  /**
   * @brief Default destructor.
   */
  ~InterReinsertion() {}

  /**
   * @brief Finds the best neighbor using reinsertion.
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
  std::string type() { return "Inter reinsertion.\n"; }

 private:
  /**
   * @brief Calculates the new times associated with a reinsertion movement.
   *
   * @param solution Current solution.
   * @param movement Reinsertion movement.
   * @param instance VRP problem instance.
   * @return The times associated with the movement.
   */
  InterReinsertionTimes GetNewTime(SolutionPtr solution,
                                   InterReinsertionMovement movement,
                                   std::shared_ptr<VRPInstance> instance);

  /**
   * @brief Verifies if a reinsertion movement is valid.
   *
   * @param solution Current solution.
   * @param times Times associated with the movement.
   * @param instance VRP problem instance.
   * @return true if the movement is valid, false otherwise.
   */
  bool IsLegalMovement(SolutionPtr solution, InterReinsertionTimes times,
                       std::shared_ptr<VRPInstance> instance);

  InterReinsertionMovement movement_;
};

#endif