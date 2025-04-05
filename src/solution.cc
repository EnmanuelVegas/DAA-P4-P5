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
}

// Operador de asignación para copia profunda
Solution& Solution::operator=(const Solution& other) {
  if (this != &other) {
    vehicles_.clear();
    total_time_ = other.total_time_;
    for (const auto& vehicle : other.vehicles_) {
      vehicles_.push_back(std::make_shared<Vehicle>(*vehicle)); // Copia profunda de cada vehículo
    }
  }
  return *this;
}


std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  os << "-> Vehicles used: " << solution.vehicles_.size() << std::endl;
  for (auto& vehicle : solution.vehicles_) {
    os << *vehicle;
  }
  double whole_time{0};
  for (auto& vehicle : solution.vehicles_) {
    whole_time += vehicle->TimeUsed();
  //   for (auto& task : vehicle->tasks()) {
  //     os << *task;
  //   }
  }
  os << "Whole time: " << whole_time << "\n";
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

bool Solution::IsRouteFeasible(int vehicle_id, VRPInstancePtr instance) {
  VehiclePtr vehicle = this->vehicles_[vehicle_id - 1];
  this->total_time_ -= vehicle->TimeUsed();
  vehicle->RestoreCapacity();
  vehicle->RestoreTime();
  int route_size = int(vehicle->route().size());
  double waste_collected{0};
  for (int j{1}; j < route_size; j++) { // Start from 1 to avoid adding depot.
    ZonePtr current_stop = vehicle->route()[j];
    ZonePtr last_stop = vehicle->route()[j - 1];
    if (instance->IsTransferStation(current_stop)) {
      waste_collected = 0;
    }
    waste_collected += current_stop->waste_quantity();
    vehicle->UpdateTime(instance->CalculateTime(last_stop->id(), current_stop->id()));
    vehicle->UpdateTime(current_stop->process_time());
    if (waste_collected > instance->collection_capacity() ||
        vehicle->remaining_time() < 0) {
      return false;
    }
  }
  this->total_time_ += vehicle->TimeUsed();
  return true;
}
