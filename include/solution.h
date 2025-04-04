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

  std::vector<VehiclePtr> vehicles() { return vehicles_; }

  // std::vector<Task> tasks() { return tasks_; }

  void PushVehicle(VehiclePtr vehicle) {
    this->vehicles_.push_back(vehicle);
  }

  double RemainingVehiclesTime();

  friend std::ostream& operator<<(std::ostream& os, const Solution& solution);


  // void PushTask(Task task) {
  //   this->tasks_.push_back(task);
  // }

 protected:
  std::vector<VehiclePtr> vehicles_;
};


#endif