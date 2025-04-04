/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file zone.h: Declaracion de la clase 'Zone'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef ZONE_H
#define ZONE_H

#include <fstream>
#include <utility>
#include <iostream>

#include "./tools/utils.h"

class Zone;

typedef std::pair<std::shared_ptr<Zone>, std::shared_ptr<Zone>> ZonePtrPair;

typedef std::shared_ptr<Zone> ZonePtr;

class Zone {
 public:
  Zone() { } // test

  Zone(int id, std::pair<int, int> coordinates, std::pair<int, int> demands);
  
  Zone(int id, std::string& input);

  double waste_quantity() { return waste_quantity_; }

  double process_time() { return process_time_; }

  int id() const { return this->id_; }

  std::pair<int, int> coordinates() const { return coordinates_; }

 protected:
  // std::pair<int, int> demands_;
  double process_time_;
  double waste_quantity_;
  std::pair<int, int> coordinates_;
  int id_;

};



#endif