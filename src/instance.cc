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
      distances_(std::vector<std::vector<double>>(0)) {
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
    ElementSetPtr new_set = std::make_shared<ElementSet>();
    for (int j{0}; j < set_size; j++) {
      input_file >> element_value;
      new_set->AddElement(element_value);
    }
    input_set_->AddSet(new_set);
  }
  // ComputeDistances();
  // for (auto& set : input_set_->sets()) {
  //   std::cout << *set;
  // }
  // ElementSetPtr prueba = input_set_->GravityCenter();
  // std::cout << "CENTRO:" << std::endl;
  // std::cout << *prueba;
  input_file.close();
  return;
}

// double Instance::GetDistance(ElementPtr actual, ElementPtr destination) {
//   int actual_id = actual->id();
//   int destination_id = destination->id();
//   if ((destination_id <= 0 || destination_id > input_elements_->Size()) ||
//       (actual_id <= 0 || actual_id > input_elements_->Size())) {
//     std::string error_positions =
//         std::to_string(actual_id) + ", " + std::to_string(destination_id);
//     throw std::out_of_range("Not permited positions: " + error_positions + ".");
//   }
//   if (actual_id >= destination_id) {
//     return distances_[actual_id - 1][destination_id - 1];
//   }
//   return distances_[destination_id - 1][actual_id - 1];
// }

// void Instance::ComputeDistances() {
//   distances_.resize(input_elements_->elements().size());
//   for (int i{0}; i < this->distances_.size(); i++) {
//     this->distances_[i] =
//         std::vector<double>(input_elements_->elements().size(), 0);
//     for (int j{0}; j < i; j++) {
//       distances_[i][j] = ComputeEuclideanDistance(
//           input_elements_->elements()[i]->position(),
//           input_elements_->elements()[j]->position());
//     }
//   }
  // for (int i{-1}; i < input_elements_->elements().size(); i++) {
  //   std::cout << std::setw(8) << i + 1 << " ";
  // }
  // std::cout << std::endl;
  // for (int i{0}; i < input_elements_->elements().size(); i++) {
  //   std::cout << std::setw(8) << i + 1 << " ";
  //   for (int j{0}; j < input_elements_->elements().size(); j++) {
  //     std::cout << std::setw(8) << distances_[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
//   return;
// }