/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef INTRA_SWAP_H
#define INTRA_SWAP_H

#include "local_search.h"

class IntraSwap : public LocalSearch {
 public:
  IntraSwap() { }

  ~IntraSwap() { }

  std::pair<bool, SolutionPtr> GetLocalOptimum(SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "Intra swap.\n"; }

 private:
  double GetNewTime(SolutionPtr new_solution, int vehicle_id, int zone_1_pos, int zone_2_pos, std::shared_ptr<VRPInstance> instance);

 private:

};

#endif