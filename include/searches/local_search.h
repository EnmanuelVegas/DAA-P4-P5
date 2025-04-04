/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>
#include <limits>
#include <algorithm>  // Para std::sort
#include <random>     // Para generar números aleatorios

#include "../vehicle.h"
#include "../vrp_instance.h"
#include "../zone.h"
#include "../task.h"
#include "../solution.h"

class LocalSearch {
 public:
  LocalSearch() { }

  virtual ~LocalSearch() { }

  virtual SolutionPtr Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) = 0;

 private:

};

#endif