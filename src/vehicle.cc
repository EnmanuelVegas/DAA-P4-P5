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

void Vehicle::AddStop(Zone zone) {
  this->route_.insert(zone);
  this->remaining_capacity_ -= zone.waste_quantity();
  return;
}

