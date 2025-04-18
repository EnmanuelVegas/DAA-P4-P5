/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.h: Declaracion de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef TRANSPORT_VEHICLE_H
#define TRANSPORT_VEHICLE_H

#include <fstream>
#include <vector>

#include "vehicle.h"

class TransportVehicle;

typedef std::shared_ptr<TransportVehicle> TransportVehiclePtr;

class TransportVehicle : public Vehicle {
 public:
  TransportVehicle(int id = 0, int time = 0, int capacity = 0)
      : Vehicle(id, time, capacity), departure_time_(0) { }

  TransportVehicle(const TransportVehicle& other);

  std::vector<TaskPtr>& tasks() { return tasks_; }

  TransportVehicle& operator=(const TransportVehicle& other);

  void AssignTask(TaskPtr task);

  double& departure_time() { return departure_time_; }

  double departure_time() const { return departure_time_; }

  double TimeLeft();// { return max_time_ - this->TimeUsed() + departure_time_; }

  // double remaining_time() const;// { return this->remaining_time_ + departure_time_; }

  double TimeUsed();//{ return this->max_time_ - this->remaining_time(); }

  friend std::ostream& operator<<(std::ostream& os, const TransportVehicle& vehicle);
 
 private:
  std::vector<TaskPtr> tasks_;
  double departure_time_;
};

#endif