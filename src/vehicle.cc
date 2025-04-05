/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/vehicle.h"

#include "../include/routes_generator.h"
#include "../include/zone.h"

void Vehicle::AddStop(ZonePtr stop_zone) {
  this->route_.emplace_back(stop_zone);
  this->remaining_capacity_ -= stop_zone->waste_quantity();
  return;
}

void Vehicle::RestoreCapacity() {
  this->remaining_capacity_ = this->max_capacity_;
  return;
}

void Vehicle::RestoreTime() {
  this->remaining_time_ = this->max_time_;
  return;
}

void Vehicle::AddTask(TaskPtr new_task) {
  this->tasks_.push_back(new_task);
  return;
}

double Vehicle::TimeUsed() {
  return this->max_time_ - this->remaining_time_;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
  os << "*** Vehicle Nº " << vehicle.id_ << " ***" << "\n";
  // os << "Remaining Time: " << vehicle.remaining_time_ << "\n";
  // os << "Remaining Capacity: " << vehicle.remaining_capacity_ << "\n";
  os << "Route: ";
  for (const auto& zone : vehicle.route_) {
    os << zone->id() << " ";
  }
  os << "\n";
  return os;




  // for (auto& vehicle : vehicles_used_) {
  //   std::cout << *vehicle;
  // }
  // for (auto& task : tasks_) {
  //   std::cout << *task;
  // }
  // std::cout << "Vehicles used: " << vehicles_used_.size() << std::endl;



}
