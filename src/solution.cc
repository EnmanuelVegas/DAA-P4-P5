/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/solution.h"

Solution::Solution(const Solution& other) : Solution() {
  collection_time_ = other.collection_time_;
  transport_time_ = other.transport_time_;
  total_time_ = other.total_time_;
  CPU_time_ = other.CPU_time_;
  for (const auto& vehicle : other.vehicles_) {
    vehicles_.push_back(std::make_shared<CollectionVehicle>(*vehicle));
  }
  for (const auto& vehicle : other.transport_vehicles_) {
    transport_vehicles_.push_back(std::make_shared<TransportVehicle>(*vehicle));
  }
}

// Operador de asignación para copia profunda
Solution& Solution::operator=(const Solution& other) {
  if (this != &other) {
    collection_time_ = other.collection_time_;
    transport_time_ = other.transport_time_;
    total_time_ = other.total_time_;
    CPU_time_ = other.CPU_time_;
    vehicles_.clear();
    for (const auto& vehicle : other.vehicles_) {
      vehicles_.push_back(std::make_shared<CollectionVehicle>(*vehicle));
    }
    for (const auto& vehicle : other.transport_vehicles_) {
      transport_vehicles_.push_back(
          std::make_shared<TransportVehicle>(*vehicle));
    }
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  os << "-> COLLECTION: " << solution.vehicles_.size() << std::endl;
  // double collection_time{0};
  for (auto& vehicle : solution.vehicles_) {
    os << *vehicle;
    // collection_time += vehicle->TimeUsed();
  }
  os << "-> TRANSPORT: " << solution.transport_vehicles_.size() << std::endl;
  // double transport_time{0};
  if (solution.transport_vehicles_.size() > 0) {
    for (auto& vehicle : solution.transport_vehicles_) {
      os << *vehicle;
      // transport_time += vehicle->TimeUsed();
      // transport_time -= vehicle->departure_time();
    }
    os << "-> Tasks: " << solution.tasks_.size() << std::endl;
    for (auto& vehicle : solution.transport_vehicles_) {
      os << "* Assigned to " << vehicle->id() << ":\n";
      for (auto& task : vehicle->tasks()) {
        os << "  " << *task;
      }
    }
  }
  os << "Whole time: " << solution.collection_time_ << " + " << solution.transport_time_ << " = "
     << solution.total_time_ << std::endl;
  return os;
}

void Solution::PrintVehicleRoute(int vehicle_id) {
  for (const auto& zone : this->vehicles_[vehicle_id - 1]->route()) {
    std::cout << zone->id() << " ";
  }
  std::cout << std::endl;
  return;
}

void Solution::PushCollectionVehicle(CollectionVehiclePtr vehicle) {
  this->vehicles_.push_back(vehicle);
  this->collection_time_ += vehicle->TimeUsed();
  return;
}


void Solution::CleanCollectionRoutes(VRPInstancePtr instance) {
  std::vector<int> delete_indexes(0);
  for (auto& vehicle : this->vehicles_) {
    bool empty = true;
    for (auto& zone : vehicle->route()) {
      if (!instance->IsTransferStation(zone) && zone->id() != instance->depot()->id()) {
        empty = false;
        break;
      }
    }
    if (empty) {
      delete_indexes.push_back(vehicle->id() - 1);
    }
  }
  // if (delete_indexes.size() > 0) {
    // std::cout << *this;
    for (auto index : delete_indexes) {
      this->collection_time_ -= this->vehicles_[index]->TimeUsed();
      vehicles_.erase(vehicles_.begin() + index);
    }
    // std::cout << *this;
  // }
  return;  
}

void Solution::AssignTransportVehicles(
    std::vector<TransportVehiclePtr>& vehicles) {
  for (auto& vehicle : vehicles) {
    this->transport_vehicles_.push_back(vehicle);
    this->transport_time_ += vehicle->TimeUsed();
    this->transport_time_ -= vehicle->departure_time();
  }
  return;
}

bool Solution::IsBetter(SolutionPtr another) {
  if (another == nullptr) {
    return true;
  }
  int vehicles_quantity = vehicles_.size() + transport_vehicles_.size();
  int other_vehicles_quantity =
      another->vehicles().size() + another->transport_vehicles().size();
  if (vehicles_quantity != other_vehicles_quantity) {
    return other_vehicles_quantity > vehicles_quantity ? true : false;
  }
  double solution_time = this->collection_time();
  double other_time = another->collection_time();
  return other_time > solution_time ? true : false;
}

void Solution::BuildTasks(VRPInstancePtr instance) {
  for (auto& vehicle : this->vehicles_) {
    double time{0};
    double waste_collected{0};
    int route_size = int(vehicle->route().size());
    for (int j{1}; j < route_size; j++) {
      ZonePtr current_stop = vehicle->route()[j];
      ZonePtr last_stop = vehicle->route()[j - 1];
      time += instance->CalculateTime(last_stop->id(), current_stop->id());
      if (instance->IsTransferStation(current_stop)) {
        TaskPtr new_task =
            std::make_shared<Task>(waste_collected, current_stop->id(), time);
        this->tasks_.push_back(new_task);
        waste_collected = 0;
      }
      waste_collected += current_stop->waste_quantity();
      time += current_stop->process_time();
    }
  }
  return;
}

void Solution::UpdateRouteTime(int vehicle_id, VRPInstancePtr instance) {
  CollectionVehiclePtr vehicle = this->vehicles_[vehicle_id - 1];
  this->collection_time_ -= vehicle->TimeUsed();
  vehicle->RestoreTime();
  int route_size = int(vehicle->route().size());
  for (int j{1}; j < route_size; j++) {
    ZonePtr current_stop = vehicle->route()[j];
    ZonePtr last_stop = vehicle->route()[j - 1];
    vehicle->UpdateTime(
        instance->CalculateTime(last_stop->id(), current_stop->id()));
    vehicle->UpdateTime(current_stop->process_time());
  }
  this->collection_time_ += vehicle->TimeUsed();
  return;
}

bool Solution::IsRouteFeasible(int vehicle_id, VRPInstancePtr instance) {
  // std::cout << "Max " << instance->collection_capacity() << std::endl;
  CollectionVehiclePtr vehicle = this->vehicles_[vehicle_id - 1];
  this->collection_time_ -= vehicle->TimeUsed();
  vehicle->RestoreCapacity();
  vehicle->RestoreTime();
  int route_size = int(vehicle->route().size());
  double waste_collected{0};
  for (int j{1}; j < route_size; j++) {  // Start from 1 to avoid adding depot.
    ZonePtr current_stop = vehicle->route()[j];
    ZonePtr last_stop = vehicle->route()[j - 1];
    if (instance->IsTransferStation(current_stop)) {
      waste_collected = 0;
    }
    waste_collected += current_stop->waste_quantity();
    // std::cout << current_stop->id() << " -> " << waste_collected <<
    // std::endl;
    vehicle->UpdateTime(
        instance->CalculateTime(last_stop->id(), current_stop->id()));
    vehicle->UpdateTime(current_stop->process_time());
    if (waste_collected > instance->collection_capacity() ||
        vehicle->remaining_time() < 0) {
      return false;
    }
  }
  this->collection_time_ += vehicle->TimeUsed();
  return true;
}
