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

#include "../include/element_set.h"




void ElementSet::AddElement(double element) {
  this->elements_.push_back(element);
}

std::ostream& operator<<(std::ostream& os, const ElementSet& set) { 
  os << "{ ";
  for (auto& element : set.elements_) {
    os << element << " ";
  }
  os << "}" << std::endl;
  return os;
}