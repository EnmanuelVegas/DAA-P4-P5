/**
 * @file element_set.h
 * @brief Declaration of the `ElementSet` class.
 *
 * This file contains the definition of the `ElementSet` class, which represents
 * a set of elements in the context of the Maximum Diversity Problem.
 *
 * @date May 6, 2025
 */

#ifndef ELEMENT_SET_H
#define ELEMENT_SET_H

#include <iostream>
#include <memory>
#include <vector>

#include "./tools/utils.h"

class ElementSet;

typedef std::shared_ptr<ElementSet> ElementSetPtr;

/**
 * @class ElementSet
 * @brief Represents a set of elements in the Maximum Diversity Problem.
 *
 * The `ElementSet` class provides methods to manage and manipulate a set of
 * elements, including adding elements, cloning, and accessing properties.
 */
class ElementSet {
 public:
  /**
   * @brief Constructs an `ElementSet` with a given ID and elements.
   *
   * @param id The unique identifier for the set.
   * @param elements A vector of elements in the set.
   */
  ElementSet(int id, std::vector<double> elements)
      : elements_(elements), id_(id) {}

  /**
   * @brief Constructs an `ElementSet` with a given ID and no elements.
   *
   * @param id The unique identifier for the set.
   */
  ElementSet(int id) : elements_(std::vector<double>(0)), id_(id) {}

  /**
   * @brief Copy constructor for `ElementSet`.
   *
   * Creates a new `ElementSet` by copying the elements and ID from another
   * `ElementSet`.
   *
   * @param other The `ElementSet` to copy.
   */
  ElementSet(const ElementSet& other)
      : elements_(other.elements_), id_(other.id_) {}

  /**
   * @brief Adds an element to the set.
   *
   * @param element The element to add.
   */
  void AddElement(double element);

  /**
   * @brief Gets the ID of the set.
   *
   * @return The unique identifier of the set.
   */
  int id() { return id_; }

  /**
   * @brief Creates a deep copy of the `ElementSet`.
   *
   * @return A shared pointer to the cloned `ElementSet`.
   */
  ElementSetPtr Clone() const;

  /**
   * @brief Gets the elements in the set as a constant reference.
   *
   * @return A constant reference to the vector of elements.
   */
  std::vector<double> elements() const { return elements_; }

  /**
   * @brief Gets the elements in the set as a mutable reference.
   *
   * @return A mutable reference to the vector of elements.
   */
  std::vector<double>& elements() { return elements_; }

  /**
   * @brief Gets the number of elements in the set.
   *
   * @return The size of the set.
   */
  int Size() { return elements_.size(); }

  /**
   * @brief Overloads the output stream operator for `ElementSet`.
   *
   * Outputs the details of the set to the given stream.
   *
   * @param os The output stream.
   * @param set The `ElementSet` instance to output.
   * @return A reference to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const ElementSet& set);

 protected:
  std::vector<double> elements_;
  int id_;
};

#endif