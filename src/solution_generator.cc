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
  best_solution = ApplyBranchAndBound(best_solution);
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
  }

  while (!nodes.empty()) {
    std::sort(nodes.begin(), nodes.end());
    std::cout << "NODOS SIN ABRIR ordenados: " << nodes.size() << std::endl;
    for (auto& node : nodes) {
      std::cout << node.partial_sol() << std::endl;
      std::cout << node.highest_limit() << std::endl;
    }
    std::cout << std::endl;


    Node open_node = nodes.front();
    nodes.erase(nodes.begin());
    std::cout << "ABRIMOS:\n";
    std::cout << open_node.partial_sol() << std::endl;
    std::cout << open_node.highest_limit() << std::endl;

    if (open_node.partial_sol().Size() == solution_size_) {
      if (open_node.partial_sol().inner_distance() > lowest_limit) {
        std::cout << "TENEMOS NUEVA COTA (Nodo abierto): " << open_node.partial_sol().inner_distance();
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

        std::cout << "METEMOS A NODO CON CONJUNTOS:" << std::endl;
        std::cout << insert_node.partial_sol() << std::endl;
        std::cout << "Y COTA SUPERIOR:" << insert_node.highest_limit() << std::endl;
        
        nodes.push_back(insert_node);
      }
    }
    for (int i = nodes.size() - 1; i >= 0; --i) {
      if (nodes[i].highest_limit() < lowest_limit) {
        std::cout << "ELIMINAMOS A NODO CON CONJUNTOS:" << std::endl;
        std::cout << nodes[i].partial_sol() << std::endl;
        std::cout << "Y COTA SUPERIOR:" << nodes[i].highest_limit() << std::endl;
        nodes.erase(nodes.begin() + i);
      }
    }
  }
  return optimal_solution;
}

double SolutionGenerator::ComputeHighestLimit(Node node) {
  int number_of_points = node.partial_sol().Size();
  SetContainer solution = node.partial_sol();
  int point_dimension = solution.sets()[0]->Size();
  while (number_of_points < solution_size_) {
    std::vector<double> coordinates;
    for (int i = 0; i < point_dimension; i++) {
      coordinates.push_back(-1);
    }
    ElementSetPtr set = std::make_shared<ElementSet>(-1, coordinates);
    solution.AddSet(set);
    number_of_points++;
  }
  double value = 0;
  for (int i = 0; i < solution.Size(); i++) {
    for (int j = i + 1; j < solution.Size(); j++) {
      if (solution.sets()[i]->id() != -1 && solution.sets()[j]->id() != -1) {
        value += ComputeEuclideanDistance(solution.sets()[i]->elements(), solution.sets()[j]->elements());
      } else {
        value += instance_->highest_distance();
      }
    }
  }
  return value;
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