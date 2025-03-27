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

VRPInstance::VRPInstance(std::string& input_name) {
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
  this->zones_[0] = std::make_shared<Zone>(-1, line);
  std::getline(input_file, line);
  this->zones_[1] = std::make_shared<Zone>(-2, line);
  std::getline(input_file, line);
  this->zones_[2] = std::make_shared<Zone>(-3, line);
  std::getline(input_file, line);
  this->zones_[3] = std::make_shared<Zone>(-4, line);
  std::getline(input_file, line);
  std::getline(input_file, line);
  std::getline(input_file, line);
  ReadZones(input_file);
  FillDistanceMatrix();
  input_file.close();
}

void VRPInstance::ReadZones(std::ifstream& filestream) {
  // std::string line{""};
  int id;
  double coord_x, coord_y, d1, d2;
  for (int i{0}; i < this->max_zones_; i++) {
    filestream >> id >> coord_x >> coord_y >> d1 >> d2;
    // std::getline(filestream, line);
    std::pair<int, int> coordinates{coord_x, coord_y};
    std::pair<int, int> demands{d1, d2}; 
    this->zones_.emplace_back(std::make_shared<Zone>(id, coordinates, demands));
  }
  return;
}


void VRPInstance::FillDistanceMatrix() {

  return;
}
