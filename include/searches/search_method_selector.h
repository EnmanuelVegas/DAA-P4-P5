/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef SEARCH_METHOD_SELECTOR_H
#define SEARCH_METHOD_SELECTOR_H

#include "./local_search.h"
#include "./intra_reinsertion.h"
#include "./inter_reinsertion.h"
#include "./intra_swap.h"
#include "./inter_swap.h"
#include "./two_opt.h"

class SearchMethodSelector {
 public:
  SearchMethodSelector(int seed = std::random_device{}());

  ~SearchMethodSelector() { }

  std::shared_ptr<LocalSearch> SelectMethod();

  bool IsEmpty();

  void Reset();

 private:
  std::vector<std::shared_ptr<LocalSearch>> search_methods_;
  std::vector<int> used_flags_;
  int active_elements_quantity_;
  std::mt19937 gen_;
};

#endif