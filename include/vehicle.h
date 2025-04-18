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

#include "task.h"
#include "vrp_instance.h"
#include "zone.h"

class Vehicle;

typedef std::shared_ptr<Vehicle> VehiclePtr;

class Vehicle {
 public:
  Vehicle(int id = 0, int time = 0, int capacity = 0)
      : id_(id),
        remaining_time_(time),
        remaining_capacity_(capacity),
        max_capacity_(capacity),
        max_time_(time),
        route_(std::vector<ZonePtr>(0)) { }

  Vehicle(const Vehicle& other);

  Vehicle& operator=(const Vehicle& other);

  void AddStop(ZonePtr zone);

  void UpdateTime(double time) { remaining_time_ -= time; }

  void DiminishCapacity(double waste) { this->remaining_capacity_ -= waste; }

  void RestoreTime();

  void RestoreCapacity();

  virtual double TimeUsed();

  int id() const { return id_; }

  virtual double remaining_time() const { return this->remaining_time_; }

  double remaining_capacity() const { return this->remaining_capacity_; }

  void UpdateRouteTime(double time_diff);

  std::vector<ZonePtr> route() const { return route_; }

  std::vector<ZonePtr>& route() { return route_; }

 protected:
  std::vector<ZonePtr> route_;
  int id_;
  double remaining_time_;
  double remaining_capacity_;
  double max_capacity_;
  double max_time_;
};

#endif