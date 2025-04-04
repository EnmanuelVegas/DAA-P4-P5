/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file task.h: Declaracion de la clase 'Task'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef TASK_H
#define TASK_H

// #include <fstream>
// #include <utility>
// #include <iostream>

#include "./tools/utils.h"

class Task;

typedef std::shared_ptr<Task> TaskPtr;

class Task {
 public:
  Task() { } // test

  Task(double waste, int transfer_id, double time)
  : waste_(waste), transfer_id_(transfer_id), time_(time) { }
  
  double waste() { return waste_; }

  int transfer_id() const { return transfer_id_; }

  double time() { return time_; }

  friend std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << "(" << task.waste_ << ", " << task.transfer_id_ << ", " << task.time_ << ")" << std::endl; 
    return os;
  }

 protected:
  double waste_;
  int transfer_id_;
  double time_;
};


#endif