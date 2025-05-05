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
 * @date  May 6, 2025
 */

#include "../include/node.h"

bool Node::operator<(const Node& other) const {
  if (this->highest_limit_ != other.highest_limit_) {
    return this->highest_limit_ < other.highest_limit_;
  }
  if (this->partial_sol().Size() != other.partial_sol().Size()) {
    return this->partial_sol().Size() < other.partial_sol().Size();
  }
  int this_last_id = this->partial_sol().sets().back()->id();
  int other_last_id = other.partial_sol().sets().back()->id();
  return this_last_id > other_last_id;
}

bool Node::operator>(const Node& other) const { return other < *this; }