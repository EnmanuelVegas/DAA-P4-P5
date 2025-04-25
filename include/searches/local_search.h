/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)

 * @file local_search.h
 * @brief Declaration of the `LocalSearch` base class.
 *
 * This file contains the definition of the `LocalSearch` base class, which
 * provides an interface for implementing various local search methods in the
 * context of the Maximum Diversity Problem.
 *
 * @date  April 29, 2025
 */

#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <algorithm>
#include <fstream>
#include <memory>
#include <random>
#include <vector>

#include "../tools/utils.h"
#include "../set_container.h"

/**
 * @class LocalSearch
 * @brief Base class for local search methods.
 *
 * The `LocalSearch` class provides a common interface for implementing
 * different local search methods for solving VRP.
 */
class LocalSearch {
 public:
  /**
   * @brief Default constructor.
   */
  LocalSearch() {}

  /**
   * @brief Default destructor.
   */
  virtual ~LocalSearch() {}

  /**
   * @brief Finds the best neighbor for the given solution.
   *
   * @param solution Current solution.
   * @param instance VRP problem instance.
   * @return A pair indicating whether a better neighbor was found and the
   * corresponding solution.
   */
  virtual bool GetBestNeighbor(SetContainerPtr solution, SetContainerPtr candidates) = 0;

  /**
   * @brief Returns the type of local search.
   *
   * @return A string describing the type of local search.
   */
  virtual std::string type() = 0;
};

#endif