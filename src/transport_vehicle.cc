/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'TransportVehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/transport_vehicle.h"

#include "../include/solution_generator.h"
#include "../include/zone.h"

double TransportVehicle::TimeLeft() const {
  return max_time_ - this->TimeUsed() + departure_time_;
}

// double TransportVehicle::remaining_time() const { return
// this->remaining_time_ + departure_time_; }

double TransportVehicle::TimeUsed() const {
  return this->max_time_ - this->remaining_time();
}

TransportVehicle::TransportVehicle(const TransportVehicle& other)
    : Vehicle(other) {
  this->departure_time_ = other.departure_time_;
  for (const auto& task : other.tasks_) {
    tasks_.push_back(std::make_shared<Task>(*task));
  }
}

// Operador de asignación para copia profunda
TransportVehicle& TransportVehicle::operator=(const TransportVehicle& other) {
  if (this != &other) {
    id_ = other.id_;
    remaining_time_ = other.remaining_time_;
    remaining_capacity_ = other.remaining_capacity_;
    max_capacity_ = other.max_capacity_;
    max_time_ = other.max_time_;
    this->departure_time_ = other.departure_time_;
    route_.clear();
    for (const auto& zone : other.route_) {
      route_.push_back(std::make_shared<Zone>(*zone));
    }
    for (const auto& task : other.tasks_) {
      tasks_.push_back(std::make_shared<Task>(*task));
    }
  }
  return *this;
}

void TransportVehicle::AssignTask(TaskPtr task) {
  this->tasks_.push_back(task);
  return;
}

std::ostream& operator<<(std::ostream& os, const TransportVehicle& vehicle) {
  os << "*** TransportVehicle Nº " << vehicle.id_ << " ***" << "\n";
  os << "Remaining Time: " << vehicle.TimeLeft() << " and departures at "
     << vehicle.departure_time_ << "\n";
  // os << "Remaining Capacity: " << vehicle.remaining_capacity_ << "\n";
  os << "Route: ";
  for (const auto& zone : vehicle.route_) {
    os << zone->id() << " ";
  }
  os << "\n";
  return os;
}
