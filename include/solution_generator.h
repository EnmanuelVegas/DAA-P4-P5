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
 * @date  April 29, 2025
 */

#ifndef SOLUTION_GENERATOR_H
#define SOLUTION_GENERATOR_H

#include <algorithm>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include "./searches/search_method_selector.h"
#include "set_container.h"
#include "instance.h"
#include "node.h"

/**
 * @class SolutionGenerator
 * @brief Generates solutions for the Maximum Diversity Problem.
 *
 * The `SolutionGenerator` class provides methods to construct and optimize
 * solutions for the VRP using various local search techniques.
 */
class SolutionGenerator {
 public:
  /**
   * @brief Constructor for `SolutionGenerator`.
   *
   * Initializes the solution generator with the given VRP instance, candidate
   * size, multistart repetitions, and random seed.
   *
   * @param instance A shared elementer to the VRP instance.
   * @param candidate_size The size of the candidate list.
   * @param multistart_rep The number of multistart repetitions.
   * @param seed The random seed (default is a random device).
   */
  SolutionGenerator(std::shared_ptr<Instance> instance, int candidate_size,
                    int solution_size, bool apply_local_search, int seed = std::random_device{}())
      : candidates_size_(candidate_size),
        solution_size_(solution_size),
        instance_(instance),
        apply_local_search_(apply_local_search),
        gen_(seed) { }  //,
                       // search_selector_(seed) {}
  

  /**
   * @brief Generates a solution for the VRP.
   *
   * Constructs a solution by building collection and transfer routes and
   * applying optimization techniques.
   *
   * @return A elementer to the generated solution.
   */
  SetContainerPtr GenerateSolution();

  SetContainerPtr BuildSolution();

  SetContainerPtr ApplyBranchAndBound(SetContainerPtr solution);

  double ComputeHighestLimit(Node node);

  ElementSetPtr GetFurthestSet(SetContainerPtr candidates, ElementSetPtr center);

 private:
  /**
   * @brief Applies the Random Variable Neighborhood Descent (VND) algorithm.
   *
   * Optimizes the solution using the Random VND algorithm.
   *
   * @param solution The initial solution.
   * @return A elementer to the optimized solution.
   */
  SetContainerPtr ApplyLocalSearch(SetContainerPtr solution);

  std::shared_ptr<Instance> instance_;
  ElementSetPtr solution_set_;
  // SearchMethodSelector search_selector_;
  std::mt19937 gen_;
  int candidates_size_;
  bool apply_local_search_;
  int solution_size_;
};

#endif