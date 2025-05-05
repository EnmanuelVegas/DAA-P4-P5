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
 * Maximum Diversity Problem.
 *
 * @date  May 6, 2025
 */

#ifndef INTER_SWAP_H
#define INTER_SWAP_H

#include "local_search.h"

/**
 * @struct InterSwapMovement
 * @brief Represents a movement in the inter-swap operation.
 *
 * This structure stores the positions of the elements to be swapped
 * between the solution and the candidates.
 */
struct InterSwapMovement {
  int solution_pos = -1;
  int candidate_pos = -1;
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
   *
   * Initializes the `InterSwap` object with a default movement.
   */
  InterSwap() : movement_(InterSwapMovement()) {}

  /**
   * @brief Default destructor.
   *
   * Cleans up the `InterSwap` object.
   */
  ~InterSwap() {}

  /**
   * @brief Finds the best neighbor using swap movements.
   *
   * This method iterates through all possible swap movements between the
   * solution and the candidates to find the best neighbor.
   *
   * @param solution Pointer to the current solution set.
   * @param candidates Pointer to the candidate set.
   * @return `true` if a better neighbor was found, `false` otherwise.
   */
  bool GetBestNeighbor(SetContainerPtr solution, SetContainerPtr candidates);

  /**
   * @brief Calculates the new inner distance after a swap movement.
   *
   * This method computes the inner distance of the solution after applying
   * a specific swap movement.
   *
   * @param movement The swap movement to be applied.
   * @param solution Pointer to the current solution set.
   * @param candidates Pointer to the candidate set.
   * @return The new inner distance after the swap.
   */
  double GetNewInnerDistance(InterSwapMovement movement,
                             SetContainerPtr solution,
                             SetContainerPtr candidates);

  /**
   * @brief Returns the type of local search.
   *
   * Provides a string describing the type of local search implemented by
   * this class.
   *
   * @return A string describing the type of local search.
   */
  std::string type() { return "Inter swap.\n"; }

 private:
  InterSwapMovement movement_;
};

#endif