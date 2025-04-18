/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file transport_vehicle.h
 * @brief Declaration of the `TransportVehicle` class.
 *
 * This file contains the definition of the `TransportVehicle` class, which
 * represents a transport vehicle in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef TRANSPORT_VEHICLE_H
#define TRANSPORT_VEHICLE_H

#include <fstream>
#include <vector>

#include "vehicle.h"

class TransportVehicle;

typedef std::shared_ptr<TransportVehicle> TransportVehiclePtr;

/**
* @class TransportVehicle
* @brief Represents a transport vehicle in the VRP.
*
* The `TransportVehicle` class inherits from `Vehicle` and provides additional
* functionality specific to transport vehicles.
*/
class TransportVehicle : public Vehicle {
public:
  /**
  * @brief Constructor for `TransportVehicle`.
  *
  * Initializes a transport vehicle with the given ID, time, and capacity.
  *
  * @param id The ID of the vehicle.
  * @param time The maximum time available for the vehicle.
  * @param capacity The maximum capacity of the vehicle.
  */
  TransportVehicle(int id = 0, int time = 0, int capacity = 0)
      : Vehicle(id, time, capacity), departure_time_(0) {}

  /**
  * @brief Copy constructor for `TransportVehicle`.
  *
  * Creates a new `TransportVehicle` by copying another instance.
  *
  * @param other The `TransportVehicle` instance to copy.
  */
  TransportVehicle(const TransportVehicle& other);

  /**
  * @brief Retrieves the tasks assigned to the transport vehicle.
  *
  * @return A reference to the vector of tasks.
  */
  std::vector<TaskPtr>& tasks() { return this->tasks_; }

  /**
  * @brief Assignment operator for `TransportVehicle`.
  *
  * Assigns the values of another `TransportVehicle` instance to this instance.
  *
  * @param other The `TransportVehicle` instance to assign.
  * @return A reference to this `TransportVehicle` instance.
  */
  TransportVehicle& operator=(const TransportVehicle& other);

  /**
  * @brief Assigns a task to the transport vehicle.
  *
  * @param task A pointer to the task to assign.
  */
  void AssignTask(TaskPtr task);

  /**
  * @brief Retrieves the departure time of the transport vehicle.
  *
  * @return A reference to the departure time.
  */
  double& departure_time() { return departure_time_; }

  /**
  * @brief Retrieves the departure time of the transport vehicle.
  *
  * @return The departure time.
  */
  double departure_time() const { return departure_time_; };

  /**
  * @brief Calculates the remaining time left for the transport vehicle.
  *
  * @return The remaining time left.
  */
  double TimeLeft() const;

  /**
  * @brief Calculates the time used by the transport vehicle.
  *
  * @return The time used.
  */
  double TimeUsed() const;

  /**
  * @brief Overloads the output stream operator for `TransportVehicle`.
  *
  * Outputs the details of the transport vehicle to the given stream.
  *
  * @param os The output stream.
  * @param vehicle The `TransportVehicle` instance to output.
  * @return A reference to the output stream.
  */
  friend std::ostream& operator<<(std::ostream& os,
                                  const TransportVehicle& vehicle);

private:
  std::vector<TaskPtr> tasks_;
  double departure_time_;
};

#endif