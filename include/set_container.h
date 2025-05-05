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

#ifndef SET_CONTAINER_H
#define SET_CONTAINER_H

#include <limits>

#include "element_set.h"

class SetContainer;

typedef std::shared_ptr<SetContainer> SetContainerPtr;

/**
 * @class SetContainer
 * @brief Represents a container for managing a collection of element sets.
 *
 * The `SetContainer` class provides methods to manage a collection of
 * `ElementSet` objects, compute distances between them, and perform
 * operations such as adding or deleting sets.
 */
class SetContainer {
  public:
   /**
    * @brief Default constructor for `SetContainer`.
    *
    * Initializes an empty container with no sets and an inner distance of 0.
    */
   SetContainer() : sets_(std::vector<ElementSetPtr>(0)), inner_distance_(0) {}
 
   /**
    * @brief Copy constructor for `SetContainer`.
    *
    * Creates a new `SetContainer` by performing a deep copy of another
    * `SetContainer`.
    *
    * @param other The `SetContainer` to copy.
    */
   SetContainer(const SetContainer& other);
 
   /**
    * @brief Assignment operator for `SetContainer`.
    *
    * Assigns the values of another `SetContainer` instance to this instance,
    * performing a deep copy of its contents.
    *
    * @param other The `SetContainer` instance to assign.
    * @return A reference to this `SetContainer` instance.
    */
   SetContainer& operator=(const SetContainer& other);
 
   /**
    * @brief Adds a set to the container.
    *
    * @param set A shared pointer to the `ElementSet` to add.
    */
   void AddSet(ElementSetPtr set);
 
   /**
    * @brief Deletes a set from the container.
    *
    * Removes the specified set from the container.
    *
    * @param delete_set A shared pointer to the `ElementSet` to delete.
    */
   void DeleteSet(ElementSetPtr delete_set);
 
   /**
    * @brief Recalculates the inner distance of the container.
    *
    * Computes the total distance between all sets in the container.
    */
   void RecalculateInnerDistance();
 
   /**
    * @brief Gets a reference to the sets in the container.
    *
    * @return A reference to the vector of `ElementSet` shared pointers.
    */
   std::vector<ElementSetPtr>& sets() { return sets_; }
 
   /**
    * @brief Gets the inner distance of the container.
    *
    * @return The total inner distance of the container.
    */
   double inner_distance() const { return inner_distance_; }
 
   /**
    * @brief Gets the number of sets in the container.
    *
    * @return The number of sets in the container.
    */
   int Size() { return sets_.size(); }
 
   /**
    * @brief Computes the gravity center of the container.
    *
    * Calculates and returns the gravity center of the sets in the container.
    *
    * @return A shared pointer to the `ElementSet` representing the gravity center.
    */
   ElementSetPtr GravityCenter();
 
   /**
    * @brief Gets the IDs of the sets in the container as a string.
    *
    * @return A string containing the IDs of the sets in the container.
    */
   std::string ContainedIDs() const;
 
   /**
    * @brief Overloads the output stream operator for `SetContainer`.
    *
    * Outputs the details of the container to the given stream.
    *
    * @param os The output stream.
    * @param container The `SetContainer` instance to output.
    * @return A reference to the output stream.
    */
   friend std::ostream& operator<<(std::ostream& os, const SetContainer& container);
 
 protected:
  std::vector<ElementSetPtr> sets_;
  double inner_distance_;
};

#endif