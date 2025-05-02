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

#ifndef SET_CONTAINER_H
#define SET_CONTAINER_H

#include <limits>

#include "element_set.h"

class SetContainer;

typedef std::shared_ptr<SetContainer> SetContainerPtr;

class SetContainer {
 public:
  /**
   * @brief Default constructor for `ElementSet`.
   *
   * Initializes an empty solution with no vehicles, tasks, or time values.
   */
  SetContainer() : sets_(std::vector<ElementSetPtr>(0)), inner_distance_(0) { }

  /**
   * @brief Assignment operator for `ElementSet`.
   *
   * Assigns the values of another `ElementSet` instance to this instance.
   *
   * @param other The `ElementSet` instance to assign.
   * @return A reference to this `ElementSet` instance.
   */
  SetContainer& operator=(const SetContainer& other);

  void AddSet(ElementSetPtr set);

  void DeleteSet(ElementSetPtr delete_set);

  void RecalculateInnerDistance();

  std::vector<ElementSetPtr>& sets() { return sets_; }

  double inner_distance() const { return inner_distance_; }

  int Size() { return sets_.size(); }

  ElementSetPtr GravityCenter();

  std::string ContainedIDs() const;


  /**
   * @brief Overloads the output stream operator for `ElementSet`.
   *
   * Outputs the details of the solution to the given stream.
   *
   * @param os The output stream.
   * @param solution The `ElementSet` instance to output.
   * @return A reference to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const SetContainer& container);

 protected:
  std::vector<ElementSetPtr> sets_;
  double inner_distance_;
};

#endif