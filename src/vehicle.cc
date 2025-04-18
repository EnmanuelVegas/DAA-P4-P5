/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/vehicle.h"

#include "../include/solution_generator.h"
#include "../include/zone.h"

Vehicle::Vehicle(const Vehicle& other)
    : id_(other.id_),
      remaining_time_(other.remaining_time_),
      remaining_capacity_(other.remaining_capacity_),
      max_capacity_(other.max_capacity_),
      max_time_(other.max_time_) {
  // Copia profunda de la ruta
  for (const auto& zone : other.route_) {
    route_.push_back(std::make_shared<Zone>(*zone));
  }
  return;
}

// Operador de asignación para copia profunda
Vehicle& Vehicle::operator=(const Vehicle& other) {
  if (this != &other) {
    id_ = other.id_;
    remaining_time_ = other.remaining_time_;
    remaining_capacity_ = other.remaining_capacity_;
    max_capacity_ = other.max_capacity_;
    max_time_ = other.max_time_;
    // Limpiar las colecciones actuales
    route_.clear();
    // tasks_.clear();
    // Copia profunda de la ruta
    for (const auto& zone : other.route_) {
      route_.push_back(std::make_shared<Zone>(*zone));
    }
  }
  return *this;
}

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

double Vehicle::TimeUsed() { return this->max_time_ - this->remaining_time(); }

void Vehicle::UpdateRouteTime(double time_diff) {
  // std::cout << "TIME DIFF: " << time_diff << std::endl;
  // std::cout << "REMAIN: " << remaining_time_ << std::endl;
  remaining_time_ = remaining_time_ - time_diff;
  // std::cout << "CURRENT: " << remaining_time_ << std::endl;
  return;
}