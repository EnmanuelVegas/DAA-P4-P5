/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file elements_set.h
 * @brief Declaration of the `ElementSet` class.
 *
 * This file contains the definition of the `ElementSet` class, which represents
 * a set of elements in the context of the Maximum Diversity Problem.
 *
 * @date  April 29, 2025
 */

#include "../include/set_container.h"

void SetContainer::AddSet(ElementSetPtr set) {
  this->sets_.push_back(set);
}

void SetContainer::DeleteSet(ElementSetPtr delete_set) {
  if (!delete_set) {
    return;
  }
  auto it = std::find(sets_.begin(), sets_.end(), delete_set);
  if (it != sets_.end()) {
    sets_.erase(it);
  }
}


ElementSetPtr SetContainer::GravityCenter() {
  ElementSetPtr center_set = std::make_shared<ElementSet>();
  if (!this->Size() || !this->sets_[0]->elements().size()) {
    return center_set;
  }
  int sets_size = sets_[0]->elements().size();
  for (int i{0}; i < sets_size; i++) {
    double center{0};
    for (int j{0}; j < sets_.size(); j++) {
      center += sets_[j]->elements()[i];
    }
    center /= sets_.size();
    center_set->AddElement(RoundToTwoDecimals(center));
  }
  return center_set;
}

std::ostream& operator<<(std::ostream& os, const SetContainer& container) { 
  os << "Solution has " << container.sets_.size() << " sets:\n";
  for (int i{0}; i < container.sets_.size(); i++) {
    os << "** Set Nº " << i + 1 << ":\n";
    os << *container.sets_[i];
  }
  return os;
}