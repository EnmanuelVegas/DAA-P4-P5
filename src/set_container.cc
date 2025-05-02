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


SetContainer& SetContainer::operator=(const SetContainer& other) {
  std::cout << "ASIGNACION" << std::endl;
  if (this != &other) {
    sets_.clear();
    sets_.reserve(other.sets_.size());
    for (const auto& set : other.sets_) {
      sets_.push_back(std::make_shared<ElementSet>(*set));
    }
    inner_distance_ = other.inner_distance_;
  }
  return *this;
}

void SetContainer::AddSet(ElementSetPtr set) {
  double added_distance{0};
  for (int i{0}; i < sets_.size(); i++) {
    added_distance += ComputeEuclideanDistance(set->elements(), sets_[i]->elements());
  }
  // std::cout << "Sumamos " << added_distance << std::endl;
  inner_distance_ += added_distance;
  this->sets_.push_back(set);
}

void SetContainer::DeleteSet(ElementSetPtr delete_set) {
  if (!delete_set) {
    return;
  }
  auto it = std::find(sets_.begin(), sets_.end(), delete_set);
  if (it != sets_.end()) {
    for (int i{0}; i < sets_.size(); i++) {
      inner_distance_ -= ComputeEuclideanDistance(delete_set->elements(), sets_[i]->elements());
    }
    sets_.erase(it);
  }
  return;
}

void SetContainer::RecalculateInnerDistance() {
  inner_distance_ = 0;
  for (int i{0}; i < sets_.size(); i++) {
    // std::cout << "Distancia de " << *sets_[i] << " con ";
    for (int j{i + 1}; j < sets_.size(); j++) {
      if (i == j) { continue; }
      // std::cout << *sets_[j] << ": ";
      inner_distance_ += ComputeEuclideanDistance(sets_[i]->elements(), sets_[j]->elements());
      // std::cout << ComputeEuclideanDistance(sets_[i]->elements(), sets_[j]->elements()) << std::endl;
    }
  }
  // // std::cout << inner_distance_ << std::endl;
  return;
}

std::string SetContainer::ContainedIDs() const {
  std::string result{""};
  for (int i{0}; i < sets_.size(); i++) {
    result += std::to_string(sets_[i]->id()) + " ";
  }
  return result;
}


ElementSetPtr SetContainer::GravityCenter() {
  ElementSetPtr center_set = std::make_shared<ElementSet>(0);
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