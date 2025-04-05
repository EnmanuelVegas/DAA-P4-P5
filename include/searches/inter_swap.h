/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef INTER_SWAP_H
#define INTER_SWAP_H

#include "local_search.h"

class InterSwap : public LocalSearch {
 public:
  InterSwap() { }

  ~InterSwap() { }

  std::pair<bool, SolutionPtr> Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

 private:

};

#endif