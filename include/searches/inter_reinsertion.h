// /**
//  * Universidad de La Laguna
//  * Escuela Superior de Ingeniería y Tecnología
//  * Grado en Ingeniería Informática
//  * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
//  *
//  * @file solution_generator.h: Declaracion de la clase 'SolutionGenerator'.
//  * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
//  */

#ifndef INTER_REINSERTION_H
#define INTER_REINSERTION_H

#include "local_search.h"

struct InterReinsertionMovement {
  int delete_vehicle_id = -1;
  int insert_vehicle_id = -1;
  int delete_zone_id = -1;
  int insert_zone_id = -1;
};

struct InterReinsertionTimes {
  InterReinsertionMovement movement = InterReinsertionMovement();
  double whole_time = -1;
  double delete_route_time = -1;
  double insert_route_time = -1;
};

class InterReinsertion : public LocalSearch {
 public:
  InterReinsertion() : movement_(InterReinsertionMovement()) {}

  ~InterReinsertion() {}

  std::pair<bool, SolutionPtr> GetBestNeighbor(
      SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "Inter reinsertion.\n"; }

 private:
  InterReinsertionTimes GetNewTime(SolutionPtr solution,
                                   InterReinsertionMovement movement,
                                   std::shared_ptr<VRPInstance> instance);

  bool CheckMovement(SolutionPtr solution, InterReinsertionTimes times,
                     std::shared_ptr<VRPInstance> instance);

  InterReinsertionMovement movement_;
};

#endif