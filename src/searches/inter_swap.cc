/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/inter_swap.h"

#include <iomanip>

bool InterSwap::GetBestNeighbor(SetContainerPtr solution, SetContainerPtr candidates) {
  // std::cout << "Distancia solución: " << solution->inner_distance() <<  std::endl;
  int solution_size = solution->sets().size();
  int candidates_size = candidates->sets().size();
  double max_inner_distance{solution->inner_distance()};
  for (int i{0}; i < solution_size; i++) {
    // std::cout << "i:" << i << std::endl;
    for (int j{0}; j < candidates_size; j++) {
      // std::cout << "j:" << j << std::endl;
      InterSwapMovement candidate_movement = {i, j};
      double candidate_inner_distance = GetNewInnerDistance(candidate_movement,
                                                            solution,
                                                            candidates);
      if (candidate_inner_distance > max_inner_distance) {
        // std::cout << "Mejor solución! " << max_inner_distance << " -> " << candidate_inner_distance << std::endl;
        movement_ = candidate_movement;
        max_inner_distance = candidate_inner_distance;
      }
    }
  }
  if (IsGreater(max_inner_distance, solution->inner_distance())) {
    // std::cout << "Antes del swap:" << std::endl;
    // std::cout << "solution->sets()[" << movement_.solution_pos << "]: " 
    //           << *solution->sets()[movement_.solution_pos] << std::endl;
    // std::cout << "candidates->sets()[" << movement_.candidate_pos << "]: " 
    //           << *candidates->sets()[movement_.candidate_pos] << std::endl;


    // std::cout << movement_.solution_pos << " " << movement_.candidate_pos << std::endl;//"]: " 
              // << *candidates->sets()[movement_.candidate_pos] << std::endl;


    // if (!solution->sets()[movement_.solution_pos] || !candidates->sets()[movement_.candidate_pos]) {
    //   std::cerr << "Error: Punteros nulos detectados." << std::endl;
    //   return false;
    // }

    // std::swap(solution->sets()[movement_.solution_pos], candidates->sets()[movement_.candidate_pos]);

    // std::cout << "Después del swap:" << std::endl;
    // std::cout << "solution->sets()[" << movement_.solution_pos << "]: " 
    //           << *solution->sets()[movement_.solution_pos] << std::endl;
    // std::cout << "candidates->sets()[" << movement_.candidate_pos << "]: " 
    //           << *candidates->sets()[movement_.candidate_pos] << std::endl;
    // ElementSetPtr out_set = solution->sets()[movement_.solution_pos];
    // ElementSetPtr in_set = candidates->sets()[movement_.candidate_pos];
    // std::cout << *solution;
    // std::cout << "Sale: " << *out_set;
    // std::cout << "Entra: "<<  *in_set;
    std::swap(solution->sets()[movement_.solution_pos], candidates->sets()[movement_.candidate_pos]);
    solution->RecalculateInnerDistance();
    candidates->RecalculateInnerDistance();
    // std::cout << *solution;
    return true;
  }
  return false;
}

double InterSwap::GetNewInnerDistance(InterSwapMovement movement,
                                    SetContainerPtr solution,
                                    SetContainerPtr candidates) {
  ElementSetPtr out_set = solution->sets()[movement.solution_pos];
  ElementSetPtr in_set = candidates->sets()[movement.candidate_pos];
  double new_inner_distance = solution->inner_distance();
  for (int i{0}; i < solution->sets().size(); i++) {
    ElementSetPtr other_set = solution->sets()[i];
    if (out_set == other_set) {
      continue;
    }
    new_inner_distance -= ComputeEuclideanDistance(out_set->elements(), other_set->elements());
    new_inner_distance += ComputeEuclideanDistance(in_set->elements(), other_set->elements());
  }
  return new_inner_distance;
}