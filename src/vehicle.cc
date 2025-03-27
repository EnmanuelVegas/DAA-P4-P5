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


void Vehicle::AddStop(ZonePtr stop_zone) {
  this->route_.emplace_back(stop_zone);
  this->remaining_capacity_ -= stop_zone->waste_quantity();
  return;
}

