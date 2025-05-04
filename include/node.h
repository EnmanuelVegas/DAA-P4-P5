/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file elements_set.h
 * @brief Declaration of the `Node` class.
 *
 * This file contains the definition of the `Node` class, which represents
 * a set of elements in the context of the Maximum Diversity Problem.
 *
 * @date  April 29, 2025
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>

#include "./set_container.h"

class Node;

typedef std::shared_ptr<Node> NodePtr;

class Node {
 public:
  /**
   * @brief Default constructor for `Node`.
   *
   * Initializes an empty solution with no vehicles, tasks, or time values.
   */
  Node() : partial_sol_(SetContainer()), highest_limit_(0.0) { }

  Node(SetContainer container) : partial_sol_(container), highest_limit_(0.0) {
    this->partial_sol_.RecalculateInnerDistance();
  }

  double& highest_limit() { return highest_limit_; }

  SetContainer partial_sol() const { return partial_sol_; }

  bool operator<(const Node& other) const;

  bool operator>(const Node& other) const;

 protected:
  SetContainer partial_sol_;
  double highest_limit_;
};

#endif