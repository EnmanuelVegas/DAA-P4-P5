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
  SetContainerPtr best_solution = BuildSolution();
  std::cout << best_solution->inner_distance();
  best_solution = ApplyLocalSearch(best_solution);
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
  std::cout << *best_solution;
  // return best_solution;
}


SetContainerPtr SolutionGenerator::BuildSolution() {
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

SetContainerPtr SolutionGenerator::ApplyLocalSearch(SetContainerPtr solution) {
  std::cout << "Antes: " << solution->inner_distance() << std::endl;
  std::shared_ptr<LocalSearch> search_method = std::make_shared<InterSwap>();
  bool search_result = true;
  while (search_result) {
    search_result = search_method->GetBestNeighbor(solution, instance_->input_set());
    std::cout << "Mejorado: " << solution->inner_distance() << std::endl;
  }
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
  return solution;
}

ElementSetPtr SolutionGenerator::GetFurthestSet(SetContainerPtr candidates, 
                                                ElementSetPtr center) {
  
  if (candidates->sets().empty()) {
    return nullptr;
  }
  std::vector<std::tuple<double, int, ElementSetPtr>> distances;
  int index = 0;
  for (const auto& candidate : candidates->sets()) {
    double distance = ComputeEuclideanDistance(center->elements(), candidate->elements());
    distances.emplace_back(distance, index, candidate);
    ++index;
  }
  std::sort(distances.begin(), distances.end(),
            [](const std::tuple<double, int, ElementSetPtr>& a,
               const std::tuple<double, int, ElementSetPtr>& b) {
              if (std::get<0>(a) == std::get<0>(b)) {
                return std::get<1>(a) < std::get<1>(b);
              }
              return std::get<0>(a) > std::get<0>(b);
            });

  // for (auto& num : distances) {
  //   std::cout << "(" << *std::get<2>(num) << " " << std::get<0>(num) << ") ";
  // }

  if (distances.size() > this->candidates_size_) {
    distances.resize(this->candidates_size_);
  }
  std::uniform_int_distribution<> dis(0, distances.size() - 1);
  int random_index = dis(this->gen_);
  // for (auto& num : distances) {
  //   std::cout << num.second->id() << " ";
  // }
  // std::cout << "Seleccionamos: " << *std::get<2>(distances[random_index]) <<
  // "\n"; std::cout << "Indice seleccionado: " << random_index << "\n";
  return std::get<2>(distances[random_index]);
}