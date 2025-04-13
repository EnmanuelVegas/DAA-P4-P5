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
#include <algorithm>  // Para std::sort
#include <fstream>
#include <iomanip>
#include <limits>
#include <memory>
#include <random>  // Para generar números aleatorios
#include <vector>

#include "../solution.h"
#include "../task.h"
#include "../tools/utils.h"
#include "../vehicle.h"
#include "../vrp_instance.h"
#include "../zone.h"

class LocalSearch {
 public:
  LocalSearch() {}

  virtual ~LocalSearch() {}

  virtual std::pair<bool, SolutionPtr> GetBestNeighbor(
      SolutionPtr solution, std::shared_ptr<VRPInstance> instance) = 0;

  virtual std::string type() = 0;
};

#endif