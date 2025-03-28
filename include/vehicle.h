/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.h: Declaracion de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <fstream>
#include <vector>

#include "zone.h"
#include "vrp_instance.h"

class Vehicle;

typedef std::shared_ptr<Vehicle> VehiclePtr;

class Vehicle {
 public:
  Vehicle(int id = 0, int time = 0, int capacity = 0 ) 
  : id_(id), remaining_time_(time), remaining_capacity_(capacity), route_() { }

  void AddStop(ZonePtr zone);

  int id() const { return id_; }

  int remaining_time() const { return this->remaining_time_; }

  int remaining_capacity() const { return this->remaining_capacity_; }

  std::vector<ZonePtr> route() { return route_; }

 private:
  std::vector<ZonePtr> route_;
  int id_;
  int remaining_time_;
  int remaining_capacity_;
};

#endif