/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file instance.h
 * @brief Declaration of the `Instance` class.
 *
 * This file contains the definition of the `Instance` class, which
 * represents an instance of the Maximum Diversity Problem.
 *
 * @date  April 29, 2025
 */

#ifndef INSTANCE_H
#define INSTANCE_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./tools/utils.h"
#include "element_set.h"
#include "set_container.h"

class Instance;

typedef std::shared_ptr<Instance> InstancePtr;

class Instance {
 public:
  Instance(std::string& input_name);

  SetContainerPtr& input_set() { return input_set_; }

  double highest_distance() { return highest_distance_; } 

  double GetDistance(int first_id, int second_id);

 private:
  SetContainerPtr input_set_;
  double highest_distance_;
  std::vector<std::vector<double>> distances_;
};

#endif