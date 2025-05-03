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

#include "../include/node.h"


bool Node::operator<(Node& other) {
  return this->highest_limit_ < other.highest_limit_;
}
