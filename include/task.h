/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 * 
 * @file task.h
 * @brief Declaration of the `Task` class.
 *
 * This file contains the definition of the `Task` class, which represents
 * a task in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef TASK_H
#define TASK_H

#include "./tools/utils.h"

class Task;

typedef std::shared_ptr<Task> TaskPtr;

/**
* @class Task
* @brief Represents a task in the VRP.
*
* The `Task` class contains information about a task, such as the waste amount,
* transfer station ID, and processing time.
*/
class Task {
public:
  /**
  * @brief Default constructor for `Task`.
  *
  * Initializes an empty task with no values.
  */
  Task() { }

  /**
  * @brief Constructor for `Task`.
  *
  * Initializes a task with the given waste amount, transfer station ID, and time.
  *
  * @param waste The amount of waste associated with the task.
  * @param transfer_id The ID of the transfer station.
  * @param time The processing time for the task.
  */
  Task(double waste, int transfer_id, double time)
      : waste_(waste), transfer_id_(transfer_id), time_(time) {}

  /**
  * @brief Retrieves the waste amount of the task.
  *
  * @return The waste amount.
  */
  double waste() { return this->waste_; }

  /**
  * @brief Retrieves the transfer station ID of the task.
  *
  * @return The transfer station ID.
  */
  int transfer_id() const { return transfer_id_; };

  /**
  * @brief Retrieves the processing time of the task.
  *
  * @return The processing time.
  */
  double time() { return time_; };

  /**
  * @brief Overloads the output stream operator for `Task`.
  *
  * Outputs the details of the task to the given stream.
  *
  * @param os The output stream.
  * @param task The `Task` instance to output.
  * @return A reference to the output stream.
  */
  friend std::ostream& operator<<(std::ostream& os, const Task& task);

protected:
  double waste_;
  int transfer_id_;
  double time_;
};

#endif