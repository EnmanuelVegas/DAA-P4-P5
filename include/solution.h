/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file task.h: Declaracion de la clase 'Task'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef SOLUTION_H
#define SOLUTION_H

// #include <fstream>
// #include <iostream>

#include "./task.h"
#include "./vehicle.h"

class Solution;

typedef std::shared_ptr<Solution> SolutionPtr;

class Solution {
 public:
  Solution() : vehicles_(std::vector<VehiclePtr>(0)) { } // test

  Solution(const Solution& other) {
    for (const auto& vehicle : other.vehicles_) {
      vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
    }
  }

  // Operador de asignación para copia profunda
  Solution& operator=(const Solution& other) {
    if (this != &other) {
      vehicles_.clear();
      for (const auto& vehicle : other.vehicles_) {
        vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
      }
    }
    return *this;
  }



  std::vector<VehiclePtr> vehicles() { return vehicles_; }

  // std::vector<Task> tasks() { return tasks_; }

  void PushVehicle(VehiclePtr vehicle) {
    this->vehicles_.push_back(vehicle);
  }

  friend std::ostream& operator<<(std::ostream& os, const Solution& solution);


  // void PushTask(Task task) {
  //   this->tasks_.push_back(task);
  // }

 protected:
  std::vector<VehiclePtr> vehicles_;
};


#endif