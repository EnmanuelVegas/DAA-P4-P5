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

struct IntraReinsertionMovement {
  int vehicle_id = -1;
  int delete_pos = -1;
  int insert_pos = -1;
};


class IntraReinsertion : public LocalSearch {
 public:
  IntraReinsertion() : movement_(IntraReinsertionMovement()) { }

  ~IntraReinsertion() { }

  std::pair<bool, SolutionPtr> GetLocalOptimum(SolutionPtr solution, std::shared_ptr<VRPInstance> instance);

  std::string type() { return "Intra reinsertion.\n"; }

 private:
 double GetNewTime(SolutionPtr solution, IntraReinsertionMovement movement, std::shared_ptr<VRPInstance> instance);

 bool CheckMovement(SolutionPtr solution, IntraReinsertionMovement movement, std::shared_ptr<VRPInstance> instance);

 IntraReinsertionMovement movement_;

};


#endif