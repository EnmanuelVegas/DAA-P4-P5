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
 * @date  May 6, 2025
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>

#include "./set_container.h"

class Node;

typedef std::shared_ptr<Node> NodePtr;


/**
 * @class Node
 * @brief Represents a node in the Maximum Diversity Problem.
 *
 * The `Node` class encapsulates a partial solution (`SetContainer`) and a
 * heuristic value (`highest_limit_`) used to evaluate the node in optimization
 * algorithms.
 */
class Node {
 public:
  /**
   * @brief Default constructor for `Node`.
   *
   * Initializes a node with an empty partial solution and a highest limit
   * value of 0.0.
   */
  Node() : partial_sol_(SetContainer()), highest_limit_(0.0) {}

  /**
   * @brief Constructs a `Node` with a given partial solution.
   *
   * Initializes the node with the provided partial solution and recalculates
   * its inner distance. The highest limit is initialized to 0.0.
   *
   * @param container The partial solution to initialize the node with.
   */
  Node(SetContainer container) : partial_sol_(container), highest_limit_(0.0) {
    this->partial_sol_.RecalculateInnerDistance();
  }

  /**
   * @brief Gets a reference to the highest limit of the node.
   *
   * @return A reference to the highest limit value.
   */
  double& highest_limit() { return highest_limit_; }

  /**
   * @brief Gets the partial solution of the node.
   *
   * @return A copy of the `SetContainer` representing the partial solution.
   */
  SetContainer partial_sol() const { return partial_sol_; }

  /**
   * @brief Compares two nodes based on their heuristic values.
   *
   * This operator is used to compare nodes in priority queues or sorting
   * algorithms.
   *
   * @param other The other node to compare with.
   * @return `true` if this node's heuristic value is less than the other's.
   */
  bool operator<(const Node& other) const;

  /**
   * @brief Compares two nodes based on their heuristic values.
   *
   * This operator is used to compare nodes in priority queues or sorting
   * algorithms.
   *
   * @param other The other node to compare with.
   * @return `true` if this node's heuristic value is greater than the other's.
   */
  bool operator>(const Node& other) const;

 protected:
  SetContainer partial_sol_;
  double highest_limit_;
};

#endif