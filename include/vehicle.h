/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.h
 * @brief Declaration of the `Vehicle` class.
 *
 * This file contains the definition of the `Vehicle` class, which represents
 * a vehicle in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <fstream>
#include <vector>

#include "task.h"
#include "vrp_instance.h"
#include "zone.h"

class Vehicle;

typedef std::shared_ptr<Vehicle> VehiclePtr;

/**
* @class Vehicle
* @brief Represents a vehicle in the VRP.
*
* The `Vehicle` class contains information about a vehicle, such as its ID,
* capacity, and route.
*/
class Vehicle {
public:
  /**
  * @brief Constructor for `Vehicle`.
  *
  * Initializes a vehicle with the given ID, maximum time, and capacity.
  *
  * @param id The ID of the vehicle.
  * @param time The maximum time available for the vehicle.
  * @param capacity The maximum capacity of the vehicle.
  */
  Vehicle(int id = 0, int time = 0, int capacity = 0)
      : id_(id),
        remaining_time_(time),
        remaining_capacity_(capacity),
        max_capacity_(capacity),
        max_time_(time),
        route_(std::vector<ZonePtr>(0)) {}

  /**
  * @brief Copy constructor for `Vehicle`.
  *
  * Creates a new `Vehicle` by copying another instance.
  *
  * @param other The `Vehicle` instance to copy.
  */
  Vehicle(const Vehicle& other);

  /**
  * @brief Assignment operator for `Vehicle`.
  *
  * Assigns the values of another `Vehicle` instance to this instance.
  *
  * @param other The `Vehicle` instance to assign.
  * @return A reference to this `Vehicle` instance.
  */
  Vehicle& operator=(const Vehicle& other);

  /**
  * @brief Adds a stop to the vehicle's route.
  *
  * @param zone A pointer to the zone to add as a stop.
  */
  void AddStop(ZonePtr zone);

  /**
  * @brief Updates the remaining time of the vehicle.
  *
  * Decreases the remaining time by the specified amount.
  *
  * @param time The amount of time to subtract.
  */
  void UpdateTime(double time) { remaining_time_ -= time; }

  /**
  * @brief Decreases the remaining capacity of the vehicle.
  *
  * @param waste The amount of waste to subtract from the remaining capacity.
  */
  void DiminishCapacity(double waste) { this->remaining_capacity_ -= waste; }

  /**
  * @brief Restores the vehicle's remaining time to its maximum value.
  */
  void RestoreTime();

  /**
  * @brief Restores the vehicle's remaining capacity to its maximum value.
  */
  void RestoreCapacity();

  /**
  * @brief Calculates the time used by the vehicle.
  *
  * @return The time used by the vehicle.
  */
  virtual double TimeUsed();

  /**
  * @brief Retrieves the ID of the vehicle.
  *
  * @return The ID of the vehicle.
  */
  int id() const { return id_; }

  /**
  * @brief Retrieves the remaining time of the vehicle.
  *
  * @return The remaining time of the vehicle.
  */
  virtual double remaining_time() const { return this->remaining_time_; }

  /**
  * @brief Retrieves the remaining capacity of the vehicle.
  *
  * @return The remaining capacity of the vehicle.
  */
  double remaining_capacity() const { return this->remaining_capacity_; }

  /**
  * @brief Updates the route time of the vehicle.
  *
  * Adjusts the route time by the specified time difference.
  *
  * @param time_diff The time difference to apply to the route time.
  */
  void UpdateRouteTime(double time_diff);

  /**
  * @brief Retrieves the route of the vehicle.
  *
  * @return A vector of zones representing the vehicle's route.
  */
  std::vector<ZonePtr> route() const { return route_; }

  /**
  * @brief Retrieves a reference to the route of the vehicle.
  *
  * @return A reference to the vector of zones representing the vehicle's route.
  */
  std::vector<ZonePtr>& route() { return route_; }

protected:
  std::vector<ZonePtr> route_;
  int id_;
  double remaining_time_;
  double remaining_capacity_;
  double max_capacity_;
  double max_time_;
};

#endif