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
 * is responsible for generating solutions for the Maximum Diversity Problem.
 *
 * @date  May 6, 2025
 */

#ifndef SOLUTION_GENERATOR_H
#define SOLUTION_GENERATOR_H

#include <algorithm>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include "instance.h"
#include "node.h"
#include "./searches/inter_swap.h"
#include "set_container.h"

/**
 * @class SolutionGenerator
 * @brief Generates solutions for the Maximum Diversity Problem.
 *
 * The `SolutionGenerator` class provides methods to construct and optimize
 * solutions for the Maximum Diversity Problem using techniques such as
 * local search and Branch and Bound.
 */
class SolutionGenerator {
 public:
  /**
   * @brief Constructor for `SolutionGenerator`.
   *
   * Initializes the solution generator with the given instance, candidate
   * size, solution size, and optional optimization techniques.
   *
   * @param instance A shared pointer to the problem instance.
   * @param candidate_size The size of the candidate list.
   * @param solution_size The size of the solution to generate.
   * @param apply_local_search Whether to apply local search optimization.
   * @param apply_byb Whether to apply Branch and Bound optimization.
   * @param seed The random seed (default is a random device).
   */
  SolutionGenerator(std::shared_ptr<Instance> instance, int candidate_size,
                    int solution_size, bool apply_local_search, bool apply_byb,
                    int seed = std::random_device{}())
          : candidates_size_(candidate_size),
          solution_size_(solution_size),
          instance_(instance),
          apply_local_search_(apply_local_search),
          apply_byb_(apply_byb),
          generated_nodes_(0),
          gen_(seed) {}  //,
                         // search_selector_(seed) {}


  /**
   * @brief Generates a solution for the Maximum Diversity Problem.
   *
   * Constructs a solution by building and optimizing it using the specified
   * techniques.
   *
   * @return A shared pointer to the generated solution.
   */
  SetContainerPtr GenerateSolution();

  /**
   * @brief Builds a solution from the given input elements.
   *
   * Constructs a solution by selecting elements from the input set.
   *
   * @param input_elements A shared pointer to the input elements.
   * @return A shared pointer to the constructed solution.
   */
  SetContainerPtr BuildSolution(SetContainerPtr input_elements);

  /**
   * @brief Computes the highest limit for a given node.
   *
   * Calculates the upper bound (highest limit) for the given node based on
   * its partial solution.
   *
   * @param node The node for which to compute the highest limit.
   * @return The computed highest limit.
   */
  double ComputeHighestLimit(Node node);

  /**
   * @brief Gets the number of nodes generated during the solution process.
   *
   * @return The number of generated nodes.
   */
  int generated_nodes() { return generated_nodes_; }

  /**
   * @brief Finds the element furthest from the given center.
   *
   * Identifies the element in the candidate set that is furthest from the
   * specified center.
   *
   * @param candidates A shared pointer to the candidate set.
   * @param center A shared pointer to the center element.
   * @return A shared pointer to the furthest element.
   */
  ElementSetPtr GetFurthestSet(SetContainerPtr candidates,
                               ElementSetPtr center);

 private:
  /**
   * @brief Applies the local search algorithm to optimize the solution.
   *
   * Optimizes the solution using a local search technique.
   *
   * @param solution The initial solution.
   * @param input_elements The input elements for the optimization process.
   * @return A shared pointer to the optimized solution.
   */
  SetContainerPtr ApplyLocalSearch(SetContainerPtr solution,
                                   SetContainerPtr input_elements);

  /**
   * @brief Applies the Branch and Bound algorithm to optimize the solution.
   *
   * Optimizes the solution using the Branch and Bound technique.
   *
   * @param solution The initial solution.
   * @return A shared pointer to the optimized solution.
   */
  SetContainerPtr ApplyBranchAndBound(SetContainerPtr solution);

  std::shared_ptr<Instance> instance_;
  ElementSetPtr solution_set_;
  // SearchMethodSelector search_selector_;
  std::mt19937 gen_;
  int candidates_size_;
  bool apply_local_search_;
  bool apply_byb_;
  int generated_nodes_;
  int solution_size_;
};

#endif