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

#ifndef ELEMENT_SET_H
#define ELEMENT_SET_H

#include <memory>
#include <vector>
#include <iostream>

#include "./tools/utils.h"

class ElementSet;

typedef std::shared_ptr<ElementSet> ElementSetPtr;

class ElementSet {
 public:
  /**
   * @brief Default constructor for `ElementSet`.
   *
   * Initializes an empty solution with no vehicles, tasks, or time values.
   */
  ElementSet(int id) : elements_(std::vector<double>(0)), id_(id) { }

  ElementSet(const ElementSet& other) : elements_(other.elements_), id_(other.id_) {}
  
  /**
   * @brief Assignment operator for `ElementSet`.
   *
   * Assigns the values of another `ElementSet` instance to this instance.
   *
   * @param other The `ElementSet` instance to assign.
   * @return A reference to this `ElementSet` instance.
   */
  // ElementSet& operator=(const ElementSet& other);

  void AddElement(double element);

  int id() { return id_; }

  std::vector<double> elements() const { return elements_; }

  std::vector<double>& elements() { return elements_; }

  int Size() { return elements_.size(); }

  /**
   * @brief Overloads the output stream operator for `ElementSet`.
   *
   * Outputs the details of the solution to the given stream.
   *
   * @param os The output stream.
   * @param solution The `ElementSet` instance to output.
   * @return A reference to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const ElementSet& set);

 protected:
  std::vector<double> elements_;
  int id_;
};

#endif