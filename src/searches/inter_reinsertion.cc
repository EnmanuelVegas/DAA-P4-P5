/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/inter_reinsertion.h"

SolutionPtr InterReinsertion::Apply(SolutionPtr solution, std::shared_ptr<VRPInstance> instance) {
  bool improvement = false;
  for (auto& vehicle : solution->vehicles()) {
    int route_size{int(vehicle->route().size())};
    for (int i{1}; i < route_size - 1; i++) {
      for (int j{1}; j < route_size - 1; j++) {
        if (i == j) {
          continue;
        }
        SolutionPtr new_solution = std::make_shared<Solution>(*solution);


      }
    }
  }
  return solution;












  // int n = ruta.size();
  // for (int i = 1; i < n; ++i) {
  //     for (int j = 1; j < n; ++j) {
  //         if (i == j) continue;
  //         vector<int> nueva = ruta;
  //         int ciudad = nueva[i];
  //         nueva.erase(nueva.begin() + i);
  //         nueva.insert(nueva.begin() + j, ciudad);
  //         if (calcularCosto(nueva, dist) < calcularCosto(ruta, dist)) {
  //             ruta = nueva;
  //             return true;
  //         }
  //     }
  // }
  // return solution;
}
