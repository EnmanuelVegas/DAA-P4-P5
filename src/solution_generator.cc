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
  SetContainerPtr best_solution = std::make_shared<SetContainer>();
  SetContainerPtr current_solution = nullptr;
  int counter{0};
  int limit{(candidates_size_ > 1) ? 500 : 1};
  while (counter++ < limit) {
    std::cout << counter << std::endl;
    current_solution = BuildSolution();
    if (apply_local_search_) {
      std::cout << "ls" << std::endl;
      current_solution = ApplyLocalSearch(current_solution); // TODO: HACER UNA TABLA CON GRASP SOLO Y OTRA CON GRASP Y BUSQUEDA LOCAL.
    }
    if (current_solution->inner_distance() > best_solution->inner_distance()) {
      best_solution = current_solution;
    }
  }
  return best_solution;
}

SetContainerPtr SolutionGenerator::BuildSolution() {
  SetContainerPtr solution = std::make_shared<SetContainer>();
  SetContainerPtr input_elements = std::make_shared<SetContainer>(*this->instance_->input_set());
  std::cout << input_elements->Size() << std::endl;
  ElementSetPtr center = input_elements->GravityCenter();
  while (solution->Size() < solution_size_) {
    ElementSetPtr furthest_set = GetFurthestSet(input_elements, center);
    solution->AddSet(furthest_set);
    input_elements->DeleteSet(furthest_set);
    center = solution->GravityCenter();
  }
  // std::cout << *solution;
  return solution;
}

SetContainerPtr SolutionGenerator::ApplyLocalSearch(SetContainerPtr solution) {
  // std::cout << "Antes: " << solution->inner_distance() << std::endl;
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