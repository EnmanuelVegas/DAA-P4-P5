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

class Zone {
 public:
  Zone() { } // test

  Zone(int id, std::pair<int, int> coordinates, std::pair<int, int> demands) 
  : id_(id), coordinates_(coordinates), demands_(demands) { }
  
  Zone(int id, std::string& input);

  double waste_quantity() { return demands_.second - demands_.first; }

  int id() const { return this->id_; }

  std::pair<int, int> coordinates() const { return coordinates_; }

 protected:
  std::pair<int, int> demands_;
  std::pair<int, int> coordinates_;
  int id_;

};



#endif