/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/search_method_selector.h"

SearchMethodSelector::SearchMethodSelector(int seed) : gen_(seed) {
  search_methods_ = std::vector<std::shared_ptr<LocalSearch>>(0);
  // search_methods_.push_back(std::make_shared<IntraReinsertion>());
  search_methods_.push_back(std::make_shared<IntraSwap>());
  // search_methods_.push_back(std::make_shared<InterReinsertion>());
  // search_methods_.push_back(std::make_shared<InterSwap>());  
  used_flags_ = std::vector<int>(search_methods_.size(), 1);
  active_elements_quantity_ = search_methods_.size();
  return;
}


std::shared_ptr<LocalSearch> SearchMethodSelector::SelectMethod() {
  std::uniform_int_distribution<> dis(1, active_elements_quantity_);
  int random_index = dis(this->gen_);
  int final_index{0};
  for (int i{0}; i < used_flags_.size(); i++) {
    if (used_flags_[i] == 1) {
      random_index--;
    }
    if (random_index == 0) {
      used_flags_[i] = 0;
      active_elements_quantity_--;
      final_index = i;
      break;
    }
  }
  return this->search_methods_[final_index];
}

bool SearchMethodSelector::IsEmpty() {
  return active_elements_quantity_ == 0;
}

void SearchMethodSelector::Reset() {
  active_elements_quantity_ = search_methods_.size();
  used_flags_.assign(search_methods_.size(), 1);
  return;
}