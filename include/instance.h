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

//   /**
//    * @brief Calculates the distance between two zones.
//    *
//    * @param actual_id The ID of the starting zone.
//    * @param destination_id The ID of the destination zone.
//    * @return The distance between the two zones.
//    */
//   double GetDistance(ElementPtr actual, ElementPtr destination);

//  private:
//   /**
//    * @brief Computes the distances between all zones in the VRP instance.
//    */
//   void ComputeDistances();

  int solution_size_;
  SetContainerPtr input_sets_;
  std::vector<std::vector<double>> distances_;
};

#endif