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

std::ostream& operator<<(std::ostream& os, const SetContainer& set) { return os; }