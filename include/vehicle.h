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
#include "task.h"

class Vehicle;

typedef std::shared_ptr<Vehicle> VehiclePtr;

class Vehicle {
 public:
  Vehicle(int id = 0, int time = 0, int capacity = 0) 
  : id_(id), remaining_time_(time), remaining_capacity_(capacity), 
  max_capacity_(capacity), max_time_(time), route_() { }

  Vehicle(const Vehicle& other)
      : id_(other.id_),
        remaining_time_(other.remaining_time_),
        remaining_capacity_(other.remaining_capacity_),
        max_capacity_(other.max_capacity_),
        max_time_(other.max_time_) {
    // Copia profunda de la ruta
    for (const auto& zone : other.route_) {
      route_.push_back(std::make_shared<Zone>(*zone));
    }
    // Copia profunda de las tareas
    for (const auto& task : other.tasks_) {
      tasks_.push_back(std::make_shared<Task>(*task));
    }
  }

  // Operador de asignación para copia profunda
  Vehicle& operator=(const Vehicle& other) {
    if (this != &other) {
      id_ = other.id_;
      remaining_time_ = other.remaining_time_;
      remaining_capacity_ = other.remaining_capacity_;
      max_capacity_ = other.max_capacity_;
      max_time_ = other.max_time_;
      // Limpiar las colecciones actuales
      route_.clear();
      tasks_.clear();
      // Copia profunda de la ruta
      for (const auto& zone : other.route_) {
        route_.push_back(std::make_shared<Zone>(*zone));
      }
      // Copia profunda de las tareas
      for (const auto& task : other.tasks_) {
        tasks_.push_back(std::make_shared<Task>(*task));
      }
    }
    return *this;
  }

  void AddStop(ZonePtr zone);

  void UpdateTime(double time) { remaining_time_ -= time; }

  void RestoreTime();

  void RestoreCapacity();

  double TimeUsed();

  void AddTask(TaskPtr new_task);

  int id() const { return id_; }

  double remaining_time() const { return this->remaining_time_; }

  double remaining_capacity() const { return this->remaining_capacity_; }

  std::vector<ZonePtr> route() const { return route_; }

  std::vector<TaskPtr> tasks() const { return tasks_; }

  std::vector<ZonePtr>& route() { return route_; }

  std::vector<TaskPtr>& tasks() { return tasks_; }

  friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);

 private:
  std::vector<ZonePtr> route_;
  std::vector<TaskPtr> tasks_;
  int id_;
  double remaining_time_;
  double remaining_capacity_;
  double max_capacity_;
  double max_time_;
};

#endif