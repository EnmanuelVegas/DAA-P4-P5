/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/zone.h"

Zone::Zone(int id, std::string& input) {
  this->zone_id_ = id;
  int space_index = SpaceIndex(input);
  std::string coordinates_string = input.substr(space_index + 1);
  space_index = SpaceIndex(coordinates_string);
  coordinates_.first = std::stoi(coordinates_string.substr(0, space_index)); 
  coordinates_.second = std::stoi(coordinates_string.substr(space_index + 1));
  return;
}


CollectionZone::CollectionZone(int id, std::pair<int, int> coordinates,
                               std::pair<int, int> demands) : Zone(id, coordinates) {
  this->demands_ = demands;
}

