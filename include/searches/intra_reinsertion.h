/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @file intra_reinsertion.h
 * @brief Declaration of the `IntraReinsertion` class and related structures.
 *
 * This file contains the definition of the `IntraReinsertion` class, which
 * implements a local search method for reinserting zones within the same route
 * in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef INTRA_REINSERTION_H
#define INTRA_REINSERTION_H

#include "local_search.h"

/**
 * @struct IntraReinsertionMovement
 * @brief Represents a reinsertion movement within a route.
 *
 * Contains the vehicle ID and the positions involved in the movement.
 */
struct IntraReinsertionMovement {
  int vehicle_id = -1;
  int delete_pos = -1;
  int insert_pos = -1;
};

/**
 * @class IntraReinsertion
 * @brief Implements a local search method for reinsertion within a route.
 *
 * The `IntraReinsertion` class inherits from `LocalSearch` and provides methods
 * to find the best neighbor using reinsertion movements.
 */
class IntraReinsertion : public LocalSearch {
 public:
  /**
   * @brief Default constructor.
   */
  IntraReinsertion() : movement_(IntraReinsertionMovement()) {}

  /**
   * @brief Default destructor.
   */
  ~IntraReinsertion() {}

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
  std::string type() { return "Intra reinsertion.\n"; }

 private:
  /**
   * @brief Calculates the new times associated with a reinsertion movement.
   *
   * @param solution Current solution.
   * @param movement Reinsertion movement.
   * @param instance VRP problem instance.
   * @return The times associated with the movement.
   */
  double GetNewTime(SolutionPtr solution, IntraReinsertionMovement movement,
                    std::shared_ptr<VRPInstance> instance);

  /**
   * @brief Verifies if a reinsertion movement is valid.
   *
   * @param solution Current solution.
   * @param movement Reinsertion movement.
   * @param instance VRP problem instance.
   * @return true if the movement is valid, false otherwise.
   */
  bool IsLegalMovement(SolutionPtr solution, IntraReinsertionMovement movement,
                       std::shared_ptr<VRPInstance> instance);

  IntraReinsertionMovement movement_;
};

#endif