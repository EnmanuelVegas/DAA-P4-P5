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
                      collection_zones_(std::vector<ZonePtr>(0)),
                      distances_collection_(std::vector<std::vector<int>>(0)),
                      distances_transfer_(std::vector<std::vector<int>>(2))  {
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
  this->depot_ = std::make_shared<Zone>(1 + max_zones_, line);
  // this->zones_.emplace_back(std::make_shared<Zone>(0, line));
  std::getline(input_file, line);
  this->transfer_stations_.first = std::make_shared<Zone>(2 + max_zones_, line);
  // this->zones_.emplace_back(std::make_shared<Zone>(-1, line));
  std::getline(input_file, line);
  this->transfer_stations_.second = std::make_shared<Zone>(3 + max_zones_, line);
  // this->zones_.emplace_back(std::make_shared<Zone>(-2, line));
  std::getline(input_file, line);
  this->dumpsite_ = std::make_shared<Zone>(4 + max_zones_, line);
  // this->zones_.emplace_back(std::make_shared<Zone>(-3, line));
  std::getline(input_file, line);
  std::getline(input_file, line);
  std::getline(input_file, line);
  ReadZones(input_file);
  FillCollectionDistances();
  FillTransferDistances();
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
    this->collection_zones_.emplace_back(std::make_shared<Zone>(id, coordinates, demands));
  }
  return;
}


// std::vector<ZonePtr> VRPInstance::collection_zones() {
//   return std::vector<ZonePtr>(zones_.begin() + 4, zones_.end());
// }


// ZonePtr VRPInstance::GetZone(int& id) { 
//   if (index < 0 || index > this->collection_zones_.size()) {
//     throw std::out_of_range("Not permited position!\n");
//   }
//   return collection_zones_.at(index);
// }

double VRPInstance::GetDistance(ZonePtr actual, int destination_id) {
  std::cout << (destination_id > this->collection_zones_.size()) << std::endl;
  if ((destination_id <= 0 || destination_id > this->collection_zones_.size() - 1) ||
       actual->id() <= 0 || actual->id() > this->collection_zones_.size() - 1) {
  std::cout << "Condition triggered: destination_id < -3 || (destination_id > 0 && destination_id > collection_zones_.size()) || "
               "actual->id() < -3 || actual->id() > collection_zones_.size()" << std::endl;
  throw std::out_of_range("Not permited position!\n");
}
  if (destination_id < this->max_zones_) {
    return GetCollectionDistance(actual->id(), destination_id);
  } else if (destination_id < 0) {
    return GetTransferDistance(actual->id(), destination_id);
  } 
  else {
    return ComputeEuclideanDistance(actual->coordinates(), depot_->coordinates());
  }

  // return ((dist_1 + dist_2 + dist_3) / speed);




}

double VRPInstance::GetCollectionDistance(int first_id, int second_id) {
  if (first_id >= second_id) {
    return distances_collection_[first_id - 1][second_id - 1];
  }
  return distances_collection_[second_id - 1][first_id - 1];
}



double VRPInstance::GetTransferDistance(int zone_id, int transfer_id) {
  if (transfer_id == -1) {
    return this->distances_transfer_[0][zone_id - 1];
  }
  return this->distances_transfer_[1][zone_id - 1];
}

void VRPInstance::FillCollectionDistances() {
  distances_collection_.resize(max_zones_);
  for (int i{0}; i < this->max_zones_; i++) {
    this->distances_collection_[i] = std::vector<int>(max_zones_, 0);
    for (int j{0}; j < i; j++) {
      distances_collection_[i][j] = ComputeEuclideanDistance(collection_zones_[i]->coordinates(),
                                              collection_zones_[j]->coordinates());
    }
  }
  // for (int i{0}; i < max_zones_; i++) {
  //   for (int j{0}; j < max_zones_; j++) {
  //     std::cout << distances_collection[i][j]<< " ";
  //   }
  //   std::cout << std::endl;
  // }
  return;
}

void VRPInstance::FillTransferDistances() {
  for (int i{0}; i < 2; i++) {
    this->distances_transfer_[i] = std::vector<int>(max_zones_, 0);
    for (int j{0}; j < max_zones_; j++) {
      if (i == 0) {
        distances_transfer_[i][j] = ComputeEuclideanDistance(
                                    transfer_stations_.first->coordinates(), 
                                    collection_zones_[j]->coordinates());
      } else {
        distances_transfer_[i][j] = ComputeEuclideanDistance(
                                    transfer_stations_.second->coordinates(), 
                                    collection_zones_[j]->coordinates());
      }
    }
  }
  return;
}

