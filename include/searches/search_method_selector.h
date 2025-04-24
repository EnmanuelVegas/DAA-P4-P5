/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file search_method_selector.h
 * @brief Declaration of the `SearchMethodSelector` class.
 *
 * This file contains the definition of the `SearchMethodSelector` class, which
 * manages the selection of local search methods for solving VRP.
 *
 * @date  April 29, 2025
 */

#ifndef SEARCH_METHOD_SELECTOR_H
#define SEARCH_METHOD_SELECTOR_H

#include "./inter_swap.h"
#include "./local_search.h"

/**
 * @class SearchMethodSelector
 * @brief Manages the selection of local search methods.
 *
 * The `SearchMethodSelector` class provides functionality to select and manage
 * different local search methods for solving VRP.
 */
class SearchMethodSelector {
 public:
  /**
   * @brief Constructor with an optional random seed.
   *
   * @param seed Random seed for method selection.
   */
  SearchMethodSelector(int seed = std::random_device{}());

  /**
   * @brief Default destructor.
   */
  ~SearchMethodSelector() {}

  /**
   * @brief Selects a local search method.
   *
   * @return A shared elementer to the selected local search method.
   */
  std::shared_ptr<LocalSearch> SelectMethod();

  /**
   * @brief Checks if there are no active search methods.
   *
   * @return true if no methods are active, false otherwise.
   */
  bool IsEmpty();

  /**
   * @brief Resets the state of the search methods.
   */
  void Reset();

 private:
  std::vector<std::shared_ptr<LocalSearch>> search_methods_;
  std::vector<int> used_flags_;
  int active_elements_quantity_;
  std::mt19937 gen_;
};

#endif