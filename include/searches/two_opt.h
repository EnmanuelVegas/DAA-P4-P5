/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file solution_generator.h: Declaracion de la clase 'SolutionGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef TWO_OPT_H
#define TWO_OPT_H

#include "local_search.h"

struct TwoOptMovement {
  int vehicle_id = -1;
  int delete_pos = -1;
  int insert_pos = -1;
};

class TwoOpt : public LocalSearch {
 public:
  TwoOpt() : movement_(TwoOptMovement()) {}

  ~TwoOpt() {}

  std::pair<bool, SolutionPtr> GetBestNeighbor(
      SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "2-opt.\n"; }

 private:
  bool CheckMovement(SolutionPtr solution, TwoOptMovement movement,
                     std::shared_ptr<VRPInstance> instance);

  TwoOptMovement movement_;
};
#endif