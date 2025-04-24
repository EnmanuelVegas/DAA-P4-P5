/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file solution_generator.h: Declaracion de la clase 'SolutionGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/solution_generator.h"

SetContainerPtr SolutionGenerator::GenerateSolution() {
  SetContainerPtr best_solution = GenerateGreedy();

  return best_solution;
  // int counter{0};
  // int not_improved{0};
  // Timer timer = Timer();
  // timer.StartStopwatch();
  // while (counter++ < this->multistart_rep_) {
    // SolutionPtr solution = BuildCollectionRoutes();
  //   solution = RandomVND(solution);
  //   solution->CleanCollectionRoutes(instance_);
  //   solution->BuildTasks(instance_);
  //   solution = BuildTransferRoutes(solution);
  //   if (solution->IsBetter(best_solution)) {
  //     best_solution = solution;
  //     not_improved = 0;
  //   }
  //   if (not_improved >= this->multistart_rep_ * 0.15) {
  //     break;
  //   }
  // }
  // best_solution->CPU_time() = timer.FinishStopwatch();
  // // std::cout << *best_solution;
  // return best_solution;
}


SetContainerPtr SolutionGenerator::GenerateGreedy() {
  SetContainerPtr solution = std::make_shared<SetContainer>();
  SetContainerPtr input_elements = this->instance_->input_set(); 
  ElementSetPtr center = input_elements->GravityCenter();
  while (solution->Size() < 5) {
    ElementSetPtr furthest_set = GetFurthestSet(input_elements, center);
    solution->AddSet(furthest_set);
    input_elements->DeleteSet(furthest_set);
    center = solution->GravityCenter();
  }
  std::cout << *solution;
  return solution;
}

SetContainerPtr SolutionGenerator::RandomVND(SetContainerPtr solution) {
  SetContainerPtr improved = std::make_shared<SetContainer>();
  // ESTA ES LA PARTE DEL CODIGO QUE SE HA MODIFICADO PARA CUMPLIR LA TAREA 3
  // search_selector_.Reset();
  // int old_time = solution->total_time();
  // // std::string result = "\n--- Random VND ---\nImproved solutions:\n";
  // while (!this->search_selector_.IsEmpty()) {
  //   std::shared_ptr<LocalSearch> search_method =
  //       search_selector_.SelectMethod();
  //   // result += "Cambiamos a " + search_method->type();
  //   // bool improved_local{false};
  //   std::pair<bool, SolutionPtr> search_result{
  //       search_method->GetBestNeighbor(solution, this->instance_)};
  //   if (search_result.first) {
  //     // result +=  "- Time: ";
  //     // result +=  std::to_string(solution->total_time()) + " --> ";
  //     solution = search_result.second;
  //     // result +=  std::to_string(solution->total_time()) + " \n";
  //     continue;
  //   }
  // }
  // // if (solution->total_time() < old_time) {
  // //   std::cout << result;
  // // }
  // return solution;
  // search_selector_.Reset();
  // int old_time = solution->total_time();
  // // std::string result = "\n--- Random VND ---\nImproved solutions:\n";
  // while (!this->search_selector_.IsEmpty()) {
  //   std::shared_ptr<LocalSearch> search_method =
  //   search_selector_.SelectMethod();
  //   // result += "Cambiamos a " + search_method->type();
  //   bool improved_local{false};
  //   while (true) {
  //     std::pair<bool, SolutionPtr>
  //     search_result{search_method->GetBestNeighbor(solution,
  //     this->instance_)}; if (search_result.first) {
  //       // result +=  "- Time: ";
  //       // result +=  std::to_string(solution->total_time()) + " --> ";
  //       solution = search_result.second;
  //       // result +=  std::to_string(solution->total_time()) + " \n";
  //       improved_local = true;
  //       continue;
  //     } else if (improved_local) {
  //       // result += "Reset!\n";
  //       this->search_selector_.Reset();
  //       break;
  //     } else {
  //       break;
  //     }
  //   }
  // }
  // // if (solution->total_time() < old_time) {
  // //   std::cout << result;
  // // }
  // return solution;
  return improved;
}

ElementSetPtr SolutionGenerator::GetFurthestSet(SetContainerPtr input_elements, 
                                                ElementSetPtr center) {
  if (input_elements->Size() == 0) {
    return nullptr;
  }
  ElementSetPtr furthest = nullptr;
  double furthest_distance{0};
  for (auto& set : input_elements->sets()) {
    double distance = ComputeEuclideanDistance(set->elements(), center->elements());
    if (distance > furthest_distance) {
      furthest = set;
    }
  }
  return furthest;
}
// ElementSetPtr SelectRandomFurthest(const ElementSetPtr& input_elements, const ElementSetPtr& center) {
//   if (input_elements->Size() == 0) {
//     return nullptr;
//   }

//   // Vector para almacenar los 3 conjuntos más alejados
//   std::vector<std::pair<double, ElementSetPtr>> furthest_sets;

//   for (auto& set : input_elements->sets()) {
//     double distance = ComputeEuclideanDistance(set->elements(), center->elements());

//     // Si aún no tenemos 3 elementos, agregamos directamente
//     if (furthest_sets.size() < 3) {
//       furthest_sets.emplace_back(distance, set);
//     } else {
//       // Si ya tenemos 3 elementos, verificamos si este es más lejano que el más cercano en la lista
//       auto min_it = std::min_element(furthest_sets.begin(), furthest_sets.end(),
//                                      [](const auto& a, const auto& b) { return a.first < b.first; });
//       if (distance > min_it->first) {
//         *min_it = {distance, set}; // Reemplazamos el más cercano con el nuevo conjunto
//       }
//     }
//   }

//   // Seleccionar aleatoriamente uno de los 3 conjuntos más alejados
//   if (!furthest_sets.empty()) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dist(0, furthest_sets.size() - 1);
//     int random_index = dist(gen);
//     return furthest_sets[random_index].second;
//   }

//   return nullptr;
// }


// ZonePtr SolutionGenerator::SelectClosestZone(ZonePtr zone,
//                                              std::vector<ZonePtr>&
//                                              candidates) {
//   if (candidates.empty()) {
//     return nullptr;
//   }
//   std::vector<std::tuple<double, int, ZonePtr>> distances;
//   int index = 0;
//   for (const auto& candidate : candidates) {
//     if (zone->id() != candidate->id()) {
//       double distance = instance_->GetDistance(zone->id(), candidate->id());
//       distances.emplace_back(distance, index, candidate);
//     }
//     ++index;
//   }
//   std::sort(distances.begin(), distances.end(),
//             [](const std::tuple<double, int, ZonePtr>& a,
//                const std::tuple<double, int, ZonePtr>& b) {
//               if (std::get<0>(a) == std::get<0>(b)) {
//                 return std::get<1>(a) < std::get<1>(b);
//               }
//               return std::get<0>(a) < std::get<0>(b);
//             });

//   // for (auto& num : distances) {
//   //   std::cout << "(" << num.second->id() << " " << num.first << ") ";
//   // }

//   if (distances.size() > this->candidates_size_) {
//     distances.resize(this->candidates_size_);
//   }
//   std::uniform_int_distribution<> dis(0, distances.size() - 1);
//   int random_index = dis(this->gen_);
//   // for (auto& num : distances) {
//   //   std::cout << num.second->id() << " ";
//   // }
//   // std::cout << "Seleccionamos: " << distances[random_index].second->id()
//   <<
//   // "\n"; std::cout << "Indice seleccionado: " << random_index << "\n";
//   return std::get<2>(distances[random_index]);
// }
