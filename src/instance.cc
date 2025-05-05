/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file instance.cc: Definición de métodos de la clase 'Instance'
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/instance.h"

Instance::Instance(std::string& input_name)
    : input_set_(std::make_shared<SetContainer>()),
      distances_(std::vector<std::vector<double>>(0)),
      max_distances_(std::vector<double>(0)) {
  std::ifstream input_file{input_name};
    if (!input_file.is_open()) {
    throw std::runtime_error("Cannot open input file!");
  }
  int set_quantity;
  int set_size;
  input_file >> set_quantity;
  input_file >> set_size;
  double element_value;
  for (int i{0}; i < set_quantity; i++) {
    ElementSetPtr new_set = std::make_shared<ElementSet>(i + 1);
    for (int j{0}; j < set_size; j++) {
      input_file >> element_value;
      new_set->AddElement(element_value);
    }
    input_set_->AddSet(new_set);
  }
  ComputeDistances();
  // for (auto& set : input_set_->sets()) {
  //   std::cout << *set;
  // }
  // ElementSetPtr prueba = input_set_->GravityCenter();
  // std::cout << "CENTRO:" << std::endl;
  // std::cout << *prueba;
  input_file.close();
  return;
}

double Instance::GetDistance(int first, int second) {
  if ((second <= 0 || second > input_set_->Size()) ||
      (first <= 0 || first > input_set_->Size())) {
    std::string error_positions = std::to_string(first) + ", " + std::to_string(second);
    throw std::out_of_range("Not permited positions: " + error_positions + ".");
  }
  if (first >= second) {
    return distances_[first - 1][second - 1];
  }
  return distances_[second - 1][first - 1];
}

double Instance::GetMaxDistance(int element_id) {
  return this->max_distances_[element_id - 1];
}


void Instance::ComputeDistances() {
  this->highest_distance_ = 0;
  distances_.resize(input_set_->sets().size());
  max_distances_.resize(input_set_->sets().size());
  for (int i{0}; i < this->distances_.size(); i++) {
    this->distances_[i] = std::vector<double>(input_set_->sets().size(), 0);
    for (int j{0}; j < i; j++) {
      double distance = ComputeEuclideanDistance(input_set_->sets()[i]->elements(),
                                                 input_set_->sets()[j]->elements());
      distances_[i][j] = distance;
      if (distance > highest_distance_) {
        highest_distance_ = distance;
      }
    }
  }
  for (int i{0}; i < distances_.size(); i++) {
    double max_distance = 0.0;
    for (int j{0}; j < distances_.at(i).size(); j++) {
      if (GetDistance(i + 1, j + 1) > max_distance) {
        max_distance = GetDistance(i + 1, j + 1);
      }
    }
    max_distances_[i] = max_distance;
  }
  // // Impresión de distancias:
  // for (int i{-1}; i < (int)input_set_->sets().size(); i++) {
  //   std::cout << std::setw(8) << i + 1 << " ";
  // }
  // std::cout << std::endl;
  // for (int i{0}; i < input_set_->sets().size(); i++) {
  //   std::cout << std::setw(8) << i + 1 << " ";
  //   for (int j{0}; j < input_set_->sets().size(); j++) {
  //     std::cout << std::setw(8) << distances_[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // for (int i{0}; i < max_distances_.size(); i++) {
  //   std::cout << max_distances_[i] << ", ";
  // }
  return;
}