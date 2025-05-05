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
  int limit{(candidates_size_ > 1) ? 20 : 1};
  while (counter++ < limit) {
    SetContainerPtr input_elements_copy = std::make_shared<SetContainer>(*this->instance_->input_set());
    current_solution = BuildSolution(input_elements_copy); // GREEDY AND GRASP
    // std::cout << *current_solution;
    if (apply_local_search_) {
      std::cout << "ls" << std::endl;
      current_solution = ApplyLocalSearch(current_solution, input_elements_copy);
    // std::cout << *current_solution;

    }
    if (current_solution->inner_distance() > best_solution->inner_distance()) {
      best_solution = current_solution;
    }
  }
  if (apply_byb_) {
    // std::cout << "byb" << std::endl;
    best_solution = ApplyBranchAndBound(best_solution);
  }
  return best_solution;
}

SetContainerPtr SolutionGenerator::BuildSolution(SetContainerPtr input_elements) {
  SetContainerPtr solution = std::make_shared<SetContainer>();
  // std::cout << *input_elements_copy;
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

SetContainerPtr SolutionGenerator::ApplyLocalSearch(SetContainerPtr solution, 
                                                    SetContainerPtr input_elements_copy) {
  // std::cout << "Antes: " << solution->inner_distance() << std::endl;
  std::shared_ptr<LocalSearch> search_method = std::make_shared<InterSwap>();
  bool search_result = true;
  while (search_result) {
    // SetContainerPtr input_elements_copy = std::make_shared<SetContainer>(*this->instance_->input_set());
    search_result = search_method->GetBestNeighbor(solution, input_elements_copy);
    std::cout << "Mejorado: " << solution->inner_distance() << std::endl;
  }
  return solution;
}

SetContainerPtr SolutionGenerator::ApplyBranchAndBound(SetContainerPtr solution) {
  double lowest_limit = solution->inner_distance();
  SetContainerPtr optimal_solution = solution;
  Node initial = Node();
  std::vector<Node> nodes;

  for (int i{0}; i < instance_->input_set()->Size(); i++) {
    SetContainer new_container = SetContainer();
    ElementSetPtr copy_set = instance_->input_set()->sets()[i]->Clone(); 
    new_container.AddSet(copy_set);
    Node insert_node(new_container);
    insert_node.highest_limit() = ComputeHighestLimit(insert_node);
    nodes.push_back(insert_node);
    ++generated_nodes_;
  }

  while (!nodes.empty()) {
    std::sort(nodes.begin(), nodes.end());
    // std::cout << "NODOS SIN ABRIR ordenados: " << nodes.size() << std::endl;
    // for (auto& node : nodes) {
    //   std::cout << node.partial_sol() << std::endl;
    //   std::cout << node.highest_limit() << std::endl;
    // }
    // std::cout << std::endl;
    Node open_node = nodes.front();
    nodes.erase(nodes.begin());
    // Node open_node = nodes.back();
    // nodes.erase(nodes.end());
    // // std::cout << "ABRIMOS:\n";
    // std::cout << open_node.partial_sol() << std::endl;
    // std::cout << open_node.highest_limit() << std::endl;
    if (open_node.partial_sol().Size() == solution_size_) {
      if (open_node.partial_sol().inner_distance() > lowest_limit) {
        // std::cout << "TENEMOS NUEVA COTA (Nodo abierto): " << open_node.partial_sol().inner_distance();
        lowest_limit = open_node.partial_sol().inner_distance();
        optimal_solution = std::make_shared<SetContainer>(open_node.partial_sol());
      }
    }
    else {
      int open_node_id = open_node.partial_sol().sets().back()->id();
      for (int i{open_node_id}; i < instance_->input_set()->Size(); i++) {
        SetContainer container = open_node.partial_sol();
        ElementSetPtr set = instance_->input_set()->sets()[i]->Clone();
        container.AddSet(set);
        Node insert_node(container);
        insert_node.highest_limit() = ComputeHighestLimit(insert_node);
        if (insert_node.highest_limit() > lowest_limit) {
          // std::cout << "METEMOS A NODO CON CONJUNTOS:" << std::endl;
          // std::cout << insert_node.partial_sol() << std::endl;
          // std::cout << "Y COTA SUPERIOR:" << insert_node.highest_limit() << std::endl;        
          nodes.push_back(insert_node);
          ++generated_nodes_;
        }
      }
    }
    for (int i = nodes.size() - 1; i >= 0; --i) {
      if (nodes[i].highest_limit() < lowest_limit) {
        nodes.erase(nodes.begin() + i);
      }
    }
  }
  return optimal_solution;
}

double SolutionGenerator::ComputeHighestLimit(Node node) {
  SetContainer solution = node.partial_sol();
  std::vector<int> used_nodes_id(0);
  for (auto& set : solution.sets()) {
    used_nodes_id.push_back(set->id());
  }
  while (solution.Size() < solution_size_) {
    double best_gain = -1;
    int best_id = -1;
    for (int i = 0; i < instance_->input_set()->Size(); ++i) {
      int candidate_id = instance_->input_set()->sets()[i]->id();
      if (std::find(used_nodes_id.begin(), used_nodes_id.end(), candidate_id) != used_nodes_id.end()) {
        continue;
      }
      double gain = 0.0;
      for (const auto& set : solution.sets()) {
        gain += instance_->GetDistance(set->id(), candidate_id);
      }
      if (gain > best_gain) {
        best_gain = gain;
        best_id = candidate_id;
      }
    }
    if (best_id == -1) break;
    ElementSetPtr best_set;
    for (int i = 0; i < instance_->input_set()->Size(); ++i) {
      int candidate_id = instance_->input_set()->sets()[i]->id();
      if (candidate_id == best_id) {
        best_set = instance_->input_set()->sets()[i]->Clone();
        break;
      }
    }
    solution.AddSet(best_set);
    used_nodes_id.push_back(best_id);
  }
  return solution.inner_distance() + instance_->highest_distance() * 0.4;
}

ElementSetPtr SolutionGenerator::GetFurthestSet(SetContainerPtr candidates, 
                                                ElementSetPtr center) {
  
  if (candidates->sets().empty()) {
    return nullptr;
  }
  std::vector<std::tuple<double, int, ElementSetPtr>> distances;
  int index = 0;
  for (const auto& candidate : candidates->sets()) {
    // double distance = ComputeEuclideanDistance(center->elements(), candidate->elements());
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