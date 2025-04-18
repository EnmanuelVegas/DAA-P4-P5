/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
/**
 * @file solution.h
 * @brief Declaration of the `Solution` class.
 *
 * This file contains the definition of the `Solution` class, which represents
 * a solution for the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include <limits>
#include <memory>
#include <vector>

#include "./collection_vehicle.h"
#include "./task.h"
#include "./transport_vehicle.h"
#include "./vehicle.h"

class Solution;

typedef std::shared_ptr<Solution> SolutionPtr;

/**
* @class Solution
* @brief Represents a solution for the Vehicle Routing Problem (VRP).
*
* The `Solution` class contains the collection and transport vehicles, tasks,
* and methods to evaluate and manipulate the solution.
*/
class Solution {
public:
  /**
  * @brief Default constructor for `Solution`.
  *
  * Initializes an empty solution with no vehicles, tasks, or time values.
  */
  Solution()
  : vehicles_(std::vector<CollectionVehiclePtr>(0)),
    transport_vehicles_(std::vector<TransportVehiclePtr>(0)),
    tasks_(std::vector<TaskPtr>(0)),
    total_time_(0),
    collection_time_(0),
    transport_time_(0) {}

  /**
  * @brief Copy constructor for `Solution`.
  *
  * Creates a new `Solution` by copying another instance.
  *
  * @param other The `Solution` instance to copy.
  */
  Solution(const Solution& other);

  /**
  * @brief Assignment operator for `Solution`.
  *
  * Assigns the values of another `Solution` instance to this instance.
  *
  * @param other The `Solution` instance to assign.
  * @return A reference to this `Solution` instance.
  */
  Solution& operator=(const Solution& other);

  /**
  * @brief Retrieves the collection vehicles in the solution.
  *
  * @return A vector of collection vehicles.
  */
  std::vector<CollectionVehiclePtr> vehicles() { return vehicles_; }

  /**
  * @brief Retrieves the transport vehicles in the solution.
  *
  * @return A vector of transport vehicles.
  */
  std::vector<TransportVehiclePtr> transport_vehicles() {
    return transport_vehicles_;
  }

  /**
  * @brief Retrieves the tasks in the solution.
  *
  * @return A vector of tasks.
  */
  std::vector<TaskPtr> tasks() { return tasks_; }

  /**
  * @brief Calculates the total time of the solution.
  *
  * @return The total time, including collection and transport times.
  */
  double total_time() const { return collection_time_ + transport_time_; }

  /**
   * @brief Retrieves the collection time of the solution.
   *
   * @return The collection time.
   */
  double collection_time() const { return this->collection_time_; }

  /**
   * @brief Retrieves the transport time of the solution.
   *
   * @return The transport time.
   */
  double transport_time() const { return this->transport_time_; }


 /**
  * @brief Assigns transport vehicles to the solution.
  *
  * @param vehicles A vector of transport vehicles to assign.
  */
  void AssignTransportVehicles(std::vector<TransportVehiclePtr>& vehicles);

  /**
  * @brief Updates the route time for a specific vehicle.
  *
  * @param vehicle_id The ID of the vehicle.
  * @param instance A pointer to the VRP instance.
  */
  void UpdateRouteTime(int vehicle_id, VRPInstancePtr instance);

  /**
  * @brief Checks if the route for a specific vehicle is feasible.
  *
  * @param vehicle_id The ID of the vehicle.
  * @param instance A pointer to the VRP instance.
  * @return true if the route is feasible, false otherwise.
  */
  bool IsRouteFeasible(int vehicle_id, VRPInstancePtr instance);

  /**
  * @brief Builds tasks for the solution based on the VRP instance.
  *
  * @param instance A pointer to the VRP instance.
  */
  void BuildTasks(VRPInstancePtr instance);

  /**
  * @brief Compares this solution with another to determine which is better.
  *
  * @param another A pointer to another solution.
  * @return true if this solution is better, false otherwise.
  */
  bool IsBetter(SolutionPtr another);

  /**
  * @brief Adds a collection vehicle to the solution.
  *
  * @param vehicle A pointer to the collection vehicle to add.
  */
  void PushCollectionVehicle(CollectionVehiclePtr vehicle);

  /**
  * @brief Prints the route of a specific vehicle.
  *
  * @param vehicle_id The ID of the vehicle.
  */
  void PrintVehicleRoute(int vehicle_id);

  /**
  * @brief Overloads the output stream operator for `Solution`.
  *
  * Outputs the details of the solution to the given stream.
  *
  * @param os The output stream.
  * @param solution The `Solution` instance to output.
  * @return A reference to the output stream.
  */
  friend std::ostream& operator<<(std::ostream& os, const Solution& solution);

protected:
  std::vector<CollectionVehiclePtr> vehicles_;
  std::vector<TransportVehiclePtr> transport_vehicles_;
  std::vector<TaskPtr> tasks_;
  double total_time_;
  double transport_time_;
  double collection_time_;
};

#endif