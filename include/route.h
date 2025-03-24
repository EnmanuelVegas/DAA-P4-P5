/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file route.h: Declaracion de la clase 'Route'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include "zone.h"

class Route {
 public:
  Route() : route_(std::vector<Zone>(0)) { }

  void Push(Zone new_zone) {
    this->route_.push_back(new_zone);
    return;
  }
 private:
  std::vector<Zone> route_;
};

#endif