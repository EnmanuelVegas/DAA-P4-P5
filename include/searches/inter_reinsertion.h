/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef INTER_REINSERTION_H
#define INTER_REINSERTION_H

#include "local_search.h"
// #include "./tools/utils.h"
// #include "vrp_instance.h"
// #include "zone.h"
// #include "task.h"

class InterReinsertion : public LocalSearch {
 public:
  InterReinsertion() { }

  ~InterReinsertion() { }

  std::pair<bool, SolutionPtr> Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

 private:

};

#endif