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

struct InterSwapMovement {
  int first_vehicle_id = -1;
  int second_vehicle_id = -1;
  int first_route_zone_id = -1;
  int second_route_zone_id = -1;
};

struct InterSwapTimes {
  InterSwapMovement movement = InterSwapMovement();
  double whole_time = -1;
  double first_route_time = -1;
  double second_route_time = -1;
};

class InterSwap : public LocalSearch {
 public:
  InterSwap() : movement_(InterSwapMovement()) {}

  ~InterSwap() {}

  std::pair<bool, SolutionPtr> GetBestNeighbor(
      SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "Inter swap.\n"; }

 private:
  InterSwapTimes GetNewTime(SolutionPtr solution, InterSwapMovement movement,
                            std::shared_ptr<VRPInstance> instance);

  bool CheckMovement(SolutionPtr solution, InterSwapTimes times,
                     std::shared_ptr<VRPInstance> instance);

  InterSwapMovement movement_;
};

#endif