/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/task.h"

std::ostream& operator<<(std::ostream& os, const Task& task) {
  os << "(" << task.waste_ << ", " << task.transfer_id_ << ", " << task.time_
     << ")" << std::endl;
  return os;
}