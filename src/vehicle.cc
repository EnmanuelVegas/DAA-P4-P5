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
#include "../include/zone.h"
#include "../include/greedy_vehicle_route.h"


void Vehicle::AddStop(ZonePtr) {
  this->route_.emplace_back(zone);
  // this->remaining_capacity_ -= zone.waste_quantity();
  return;
}

