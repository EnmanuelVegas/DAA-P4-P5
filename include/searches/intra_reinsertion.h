/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef INTRA_REINSERTION_H
#define INTRA_REINSERTION_H

#include "local_search.h"

class IntraReinsertion : public LocalSearch {
 public:
  IntraReinsertion() { }

  ~IntraReinsertion() { }

  std::pair<bool, SolutionPtr> Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "Intra reinsertion.\n"; }

 private:

};

#endif