/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file instance.h
 * @brief Declaration of the `Instance` class.
 *
 * This file contains the definition of the `Instance` class, which
 * represents an instance of the Maximum Diversity Problem.
 *
 * @date May 6, 2025
 */

#ifndef INSTANCE_H
#define INSTANCE_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./tools/utils.h"
#include "element_set.h"
#include "set_container.h"

class Instance;

typedef std::shared_ptr<Instance> InstancePtr;

/**
 * @class Instance
 * @brief Represents an instance of the Maximum Diversity Problem.
 *
 * The `Instance` class provides methods to manage and analyze an instance
 * of the Maximum Diversity Problem, including reading input data, computing
 * distances, and accessing problem-specific properties.
 */
class Instance {
 public:
  /**
   * @brief Constructs an `Instance` object from an input file.
   *
   * Reads the input data from the specified file and initializes the
   * instance with the corresponding elements and distances.
   *
   * @param input_name The name of the input file.
   */
  Instance(std::string& input_name);

  /**
   * @brief Gets the input set of the instance.
   *
   * @return A reference to the `SetContainer` containing the input set.
   */
  SetContainerPtr& input_set() { return input_set_; }

  /**
   * @brief Gets the highest distance in the instance.
   *
   * @return The highest distance between any two elements in the instance.
   */
  double highest_distance() { return highest_distance_; }

  /**
   * @brief Gets the distance between two elements by their IDs.
   *
   * @param first_id The ID of the first element.
   * @param second_id The ID of the second element.
   * @return The distance between the two elements.
   */
  double GetDistance(int first_id, int second_id);

  /**
   * @brief Gets the max distance between a element and any other (for heuristics).
   *
   * @param element_id The ID of the element.
   * @return The maxdistance between an element and any other.
   */
  double GetMaxDistance(int element_id);

 private:
  /**
   * @brief Computes the pairwise distances between all elements.
   *
   * This method calculates and stores the distances between all pairs
   * of elements in the instance.
   */
  void ComputeDistances();
 
  double highest_distance_;
  SetContainerPtr input_set_;
  std::vector<std::vector<double>> distances_;
  std::vector<double> max_distances_;
};

#endif