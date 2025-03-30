/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.cc: Definición de métodos de la clase 'VRPTransshipments'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/vrp_instance.h"

VRPInstance::VRPInstance(std::string& input_name) :
                      zones_(std::vector<ZonePtr>(0)),
                      distances_(std::vector<std::vector<double>>(0)) {
  std::ifstream input_file{input_name};
  if(!input_file.is_open()) {
    throw std::runtime_error("Cannot open input file!");
  }
  std::string line{""};
  std::getline(input_file, line);
  max_collection_time_ = std::stoi(line.substr(3));
  std::getline(input_file, line);
  max_transport_time_ = std::stoi(line.substr(3));
  std::getline(input_file, line);
  max_vehicles_ = std::stoi(line.substr(SpaceIndex(line) + 1));
  std::getline(input_file, line);
  max_zones_ = std::stoi(line.substr(SpaceIndex(line) + 1));
  std::getline(input_file, line);
  std::getline(input_file, line);
  std::getline(input_file, line);
  collection_capacity_ = std::stoi(line.substr(SpaceIndex(line) + 1));
  std::getline(input_file, line);
  transport_capacity_ = std::stoi(line.substr(SpaceIndex(line) + 1));
  std::getline(input_file, line);
  speed_ = std::stoi(line.substr(SpaceIndex(line) + 1));
  std::getline(input_file, line);
  ZonePtr depot = std::make_shared<Zone>(1 + max_zones_, line);
  std::getline(input_file, line);
  ZonePtr first_transfer = std::make_shared<Zone>(2 + max_zones_, line);
  std::getline(input_file, line);
  ZonePtr second_transfer = std::make_shared<Zone>(3 + max_zones_, line);
  std::getline(input_file, line);
  ZonePtr dumpsite = std::make_shared<Zone>(4 + max_zones_, line);
  std::getline(input_file, line);
  std::getline(input_file, line);
  std::getline(input_file, line);
  ReadZones(input_file);
  this->zones_.emplace_back(depot);
  zones_.emplace_back(first_transfer);
  zones_.emplace_back(second_transfer);
  zones_.emplace_back(dumpsite);
  ComputeDistances();
  input_file.close();
}

void VRPInstance::ReadZones(std::ifstream& filestream) {
  int id;
  double coord_x, coord_y, d1, d2;
  for (int i{0}; i < this->max_zones_; i++) {
    filestream >> id >> coord_x >> coord_y >> d1 >> d2;
    std::pair<int, int> coordinates{coord_x, coord_y};
    std::pair<int, int> demands{d1, d2}; 
    this->zones_.emplace_back(std::make_shared<Zone>(id, coordinates, demands));
  }
  return;
}

std::vector<ZonePtr> VRPInstance::collection_zones() {
  return std::vector<ZonePtr>(zones_.begin(), zones_.end() - 4);
}

double VRPInstance::GetDistance(int actual_id, int destination_id) {
  // std::cout << (destination_id > this->zones_.size()) << std::endl;
  if ((destination_id <= 0 || destination_id > this->zones_.size() + 4 - 1) ||
       actual_id <= 0 || actual_id > this->zones_.size() + 4 - 1) {
      throw std::out_of_range("Not permited position!\n");
  }
  if (actual_id >= destination_id) {
    return distances_[actual_id - 1][destination_id - 1];
  }
  return distances_[destination_id - 1][actual_id - 1];
}

void VRPInstance::ComputeDistances() {
  distances_.resize(max_zones_ + 4);
  for (int i{0}; i < this->distances_.size(); i++) {
    this->distances_[i] = std::vector<double>(max_zones_ + 4, 0);
    for (int j{0}; j < i; j++) {
      distances_[i][j] = ComputeEuclideanDistance(zones_[i]->coordinates(),
                                                  zones_[j]->coordinates());
    }
  }
  for (int i{-1}; i < max_zones_ + 4; i++) {
    std::cout << std::setw(8) << i + 1 << " ";  // Ancho fijo de 5 caracteres
  }
  std::cout << std::endl;
  for (int i{0}; i < max_zones_ + 4; i++) {
    std::cout << std::setw(8) << i + 1 << " ";  // Ancho fijo de 5 caracteres
    for (int j{0}; j < max_zones_ + 4; j++) {
      std::cout << std::setw(8) << distances_[i][j] << " ";  // Ancho fijo de 5 caracteres
    }
    std::cout << std::endl;
  }
  return;
}