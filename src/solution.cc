/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/solution.h"

Solution::Solution(const Solution& other) : Solution() {
  total_time_ = other.total_time_;
  for (const auto& vehicle : other.vehicles_) {
    vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
  }
  for (const auto& vehicle : other.transport_vehicles_) {
    vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
  }
  improvements_counter_ = other.improvements_counter_;
}

// Operador de asignación para copia profunda
Solution& Solution::operator=(const Solution& other) {
  if (this != &other) {
    improvements_counter_ = other.improvements_counter_;
    total_time_ = other.total_time_;
    vehicles_.clear();
    for (const auto& vehicle : other.vehicles_) {
      vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
    }
    for (const auto& vehicle : other.transport_vehicles_) {
      vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
    }
  }
  return *this;
}


std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  os << "-> Collection Vehicles: " << solution.vehicles_.size() << std::endl;
  double collection_time{0};
  for (auto& vehicle : solution.vehicles_) {
    os << *vehicle;
    collection_time += vehicle->TimeUsed();
  }
  os << "-> Transport Vehicles: " << solution.transport_vehicles_.size() << std::endl;
  double transport_time{0};
  for (auto& vehicle : solution.transport_vehicles_) {
    os << *vehicle;
    transport_time += vehicle->TimeUsed();
  }
  os << "-> Tasks: " << std::endl;
  for (auto& vehicle : solution.transport_vehicles_) {
    for (auto& task : vehicle->tasks()) {
      os << *task;
    }
  }
  os << "Whole time: " << collection_time << " + " << transport_time << " = "
     << collection_time + transport_time << std::endl;
  return os;
}

void Solution::PrintVehicleRoute(int vehicle_id) {
  for (const auto& zone : this->vehicles_[vehicle_id - 1]->route()) {
    std::cout << zone->id() << " ";
  }
  std::cout << "\n";
  return;
}

void Solution::PushVehicle(VehiclePtr vehicle) {
  this->vehicles_.push_back(vehicle);
  this->total_time_ += vehicle->TimeUsed();
  return;
}

void Solution::AssignTransportVehicles(std::vector<VehiclePtr>& vehicles) {
  for (auto& vehicle : vehicles) {
    // std::cout << *vehicle;
    this->transport_vehicles_.push_back(vehicle);
    // std::cout << this->transport_vehicles_.size();
  }
  return;
}

bool Solution::IsBetter(SolutionPtr another) {
  if (another == nullptr) {
    return true;
  }
  // int vehicles_quantity = vehicles_.size() + transport_vehicles_.size();
  // int other_vehicles_quantity = another->vehicles().size() + another->transport_vehicles().size();
  // if (vehicles_quantity < other_vehicles_quantity) {
  //   return true;
  // }
  // else if (vehicles_quantity > other_vehicles_quantity) {
  //   return false;
  // }
  double solution_time = this->total_time_;
  double other_time = another->total_time();
  if (solution_time < other_time) {
    return true;
  }
  return false;
}


void Solution::BuildTasks(VRPInstancePtr instance) {
  for (auto& vehicle : this->vehicles_) {
    double time{0};
    double waste_collected{0};
    int route_size = int(vehicle->route().size());
    for (int j{1}; j < route_size; j++) { // Start from 1 to avoid adding depot.
      ZonePtr current_stop = vehicle->route()[j];
      ZonePtr last_stop = vehicle->route()[j - 1];
      time += instance->CalculateTime(last_stop->id(), current_stop->id());
      if (instance->IsTransferStation(current_stop)) {
        TaskPtr new_task = std::make_shared<Task>(waste_collected, current_stop->id(), time);
        this->tasks_.push_back(new_task);
        waste_collected = 0;
      }
      waste_collected += current_stop->waste_quantity();
      time += current_stop->process_time();
    }
  }
  return;
}

void Solution::UpdateTotalTime(int vehicle_id, VRPInstancePtr instance) {
  // std::cout << "Max " << instance->collection_capacity() << std::endl;
  VehiclePtr vehicle = this->vehicles_[vehicle_id - 1];
  // std::cout << "Desde dentro" << std::endl;
  // for (auto& zone : vehicle->route()) {
  //   std::cout << zone->id() << " ";
  // } 
  // std::cout << std::endl;

  
  // std::cout << "Total " << this->total_time_ << std::endl;
  this->total_time_ -= vehicle->TimeUsed();
  // std::cout << "Total " << this->total_time_ << std::endl;
  // std::cout << "CAR BEFORE: " << vehicle->remaining_time();
  vehicle->RestoreTime();
  int route_size = int(vehicle->route().size());
  for (int j{1}; j < route_size; j++) {
    ZonePtr current_stop = vehicle->route()[j];
    ZonePtr last_stop = vehicle->route()[j - 1];
    // std::cout << current_stop->id() << " -> " << waste_collected << std::endl;
    vehicle->UpdateTime(instance->CalculateTime(last_stop->id(), current_stop->id()));
    vehicle->UpdateTime(current_stop->process_time());
    // std::cout << "CAR: " << vehicle->remaining_time();
  }
  this->total_time_ += vehicle->TimeUsed();
  // std::cout << "After recalculation " << this->total_time_ << std::endl;
  return;
}



bool Solution::IsRouteFeasible(int vehicle_id, VRPInstancePtr instance) {
  // std::cout << "Max " << instance->collection_capacity() << std::endl;
  VehiclePtr vehicle = this->vehicles_[vehicle_id - 1];
  // this->total_time_ -= vehicle->TimeUsed();
  vehicle->RestoreCapacity();
  // vehicle->RestoreTime();
  int route_size = int(vehicle->route().size());
  double waste_collected{0};
  for (int j{1}; j < route_size; j++) { // Start from 1 to avoid adding depot.
    ZonePtr current_stop = vehicle->route()[j];
    ZonePtr last_stop = vehicle->route()[j - 1];
    if (instance->IsTransferStation(current_stop)) {
      waste_collected = 0;
    }
    waste_collected += current_stop->waste_quantity();
    // std::cout << current_stop->id() << " -> " << waste_collected << std::endl;
    // vehicle->UpdateTime(instance->CalculateTime(last_stop->id(), current_stop->id()));
    // vehicle->UpdateTime(current_stop->process_time());
    if (waste_collected > instance->collection_capacity()) {// ||
        // vehicle->remaining_time() < 0) {
      return false;
    }
  }
  // vehicle->MarkAsModified();
  // this->total_time_ += vehicle->TimeUsed();
  return true;
}
