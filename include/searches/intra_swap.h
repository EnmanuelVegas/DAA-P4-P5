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

struct IntraSwapMovement {
  int vehicle_id = -1;
  int first_zone_id = -1;
  int second_zone_id = -1;
};

class IntraSwap : public LocalSearch {
 public:
  IntraSwap() : movement_(IntraSwapMovement()) {}

  ~IntraSwap() {}

  std::pair<bool, SolutionPtr> GetBestNeighbor(
      SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "Intra swap.\n"; }

 private:
  double GetNewTime(SolutionPtr solution, IntraSwapMovement movement,
                    std::shared_ptr<VRPInstance> instance);

  bool CheckMovement(SolutionPtr solution, IntraSwapMovement movement,
                     std::shared_ptr<VRPInstance> instance);

  IntraSwapMovement movement_;
};

#endif