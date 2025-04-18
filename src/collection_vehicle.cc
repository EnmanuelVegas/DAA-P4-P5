/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'CollectionVehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/collection_vehicle.h"

#include "../include/solution_generator.h"
#include "../include/zone.h"

CollectionVehicle::CollectionVehicle(const CollectionVehicle& other)
    : Vehicle(other) { }

// Operador de asignación para copia profunda
CollectionVehicle& CollectionVehicle::operator=(const CollectionVehicle& other) {
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

std::ostream& operator<<(std::ostream& os, const CollectionVehicle& vehicle) {
  os << "*** CollectionVehicle Nº " << vehicle.id_ << " ***" << "\n";
  os << "Remaining Time: " << vehicle.remaining_time_ << "\n";
  // os << "Remaining Capacity: " << vehicle.remaining_capacity_ << "\n";
  os << "Route: ";
  for (const auto& zone : vehicle.route_) {
    os << zone->id() << " ";
  }
  os << "\n";
  return os;
}
