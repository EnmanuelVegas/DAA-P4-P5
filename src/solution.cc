/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/solution.h"

std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  os << "-> Vehicles used: " << solution.vehicles_.size() << std::endl;
  for (auto& vehicle : solution.vehicles_) {
    os << *vehicle;
  }
  double whole_time{0};
  for (auto& vehicle : solution.vehicles_) {
    whole_time += vehicle->TimeUsed();
    for (auto& task : vehicle->tasks()) {
      os << *task;
    }
  }
  os << "Whole time: " << whole_time << "\n";
  return os;
}