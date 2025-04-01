/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../include/routes_generator.h"

#include <fstream>
#include <vector>

std::vector<VehiclePtr> RoutesGenerator::Generate() {
  // Greedy Requirements
  std::vector<ZonePtr> zones = instance_->collection_zones();
  double collection_capacity = instance_->collection_capacity();
  double max_time = instance_->max_collection_time();
  ZonePtrPair transport_zones = instance_->transfer_stations();
  ZonePtr depot = instance_->depot();
  // Greedy execution
  this->vehicles_used_.clear();
  int vehicle_index = 1;
  while (!zones.empty()) {
    VehiclePtr current_vehicle = std::make_shared<Vehicle>(vehicle_index, max_time, collection_capacity);
    current_vehicle->AddStop(depot);
    while (true) {
      ZonePtr last_stop = current_vehicle->route().back();
      ZonePtr closest = SelectClosestZone(last_stop, zones);
      if (closest == nullptr) { break; }
      double return_depot_time = ReturnToDepotTime(last_stop, closest->id());
      if (closest->waste_quantity() <= current_vehicle->remaining_capacity() &&
          return_depot_time <= current_vehicle->remaining_time()) {
        AddNormalStop(last_stop, closest, current_vehicle);
        zones.erase(find(zones.begin(), zones.end(), closest));
      } else if (return_depot_time <= current_vehicle->remaining_time()) {
        ZonePtr closest_transfer = SelectClosestTransferStation(last_stop->id()); // REVISAR CON EL PSEUDOCÓDIGO: last_stop o closest_zone?
        AddTransferStop(last_stop, closest_transfer, current_vehicle, collection_capacity, max_time);        
      } else {
        break;
      }
    }
    ZonePtr last_stop = current_vehicle->route().back();
    if (!BelongsTo(last_stop, transport_zones)) {
      ZonePtr closest_transport = SelectClosestTransferStation(last_stop->id());
      AddTransferStop(last_stop, closest_transport, current_vehicle, collection_capacity, max_time);
      AddNormalStop(closest_transport, depot, current_vehicle);
    } else {
      AddNormalStop(last_stop, depot, current_vehicle);
    }
    vehicles_used_.push_back(current_vehicle);
    vehicle_index++;
  }
  for (auto& vehicle : vehicles_used_) {
    std::cout << *vehicle;
  }
  for (auto& task : tasks_) {
    std::cout << *task;
  }
  std::cout << "Vehicles used:" << vehicles_used_.size() << std::endl;
  return this->vehicles_used_;
}

double RoutesGenerator::CalculateTime(int actual_id, int destination_id) {
  return (instance_->GetDistance(actual_id, destination_id) /
          instance_->speed()) * 60;
}

double RoutesGenerator::ReturnToDepotTime(ZonePtr actual_zone, int closest_id) {
  // dist_1 = Current zone to closest collection zone.
  double dist_1 = instance_->GetDistance(actual_zone->id(), closest_id);
  ZonePtr transfer = SelectClosestTransferStation(closest_id);
  // dist_2 = closest collection to closest SWTS.
  double dist_2 = instance_->GetDistance(closest_id, transfer->id());
  // dist_3 = SWTS to depot.
  double dist_3 =
      instance_->GetDistance(transfer->id(), instance_->depot()->id());
  int speed = instance_->speed();
  // time = distance / speed
  return ((dist_1 + dist_2 + dist_3) / speed) * 60;
}

ZonePtr RoutesGenerator::SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates) {
  if (candidates.empty()) {
    return nullptr;
  }
  // Crear un vector de pares (distancia, ZonePtr)
  std::vector<std::pair<double, ZonePtr>> distances;
  for (const auto& candidate : candidates) {
    if (zone->id() != candidate->id()) {  // Evitar comparar con la misma zona
      double distance = instance_->GetDistance(zone->id(), candidate->id());
      distances.emplace_back(distance, candidate);
    }
  }
  // Ordenar los candidatos por distancia
  std::sort(distances.begin(), distances.end(),
            [](const std::pair<double, ZonePtr>& a, const std::pair<double, ZonePtr>& b) {
              return a.first < b.first;
            });
  // Limitar a los `n` elementos más cercanos
  if (distances.size() > this->candidates_size_) {
    distances.resize(this->candidates_size_);
  }
  // Seleccionar aleatoriamente uno de los `n` elementos más cercanos
  std::uniform_int_distribution<> dis(0, distances.size() - 1);  // Crear la distribución
  int random_index = dis(this->gen_);
  return distances[random_index].second;  // Retornar el ZonePtr seleccionado
}

void RoutesGenerator::AddNormalStop(ZonePtr last, ZonePtr closest, VehiclePtr vehicle) {
  vehicle->AddStop(closest);  // It also substracts the capacity.
  double visit_closest_time = CalculateTime(last->id(), closest->id());
  vehicle->UpdateTime(visit_closest_time);  
  return;
}

void RoutesGenerator::AddTransferStop(ZonePtr last, ZonePtr transfer, VehiclePtr vehicle,
                                     double capacity, double max_time) {
  double visit_transfer_time = CalculateTime(last->id(), transfer->id());
  vehicle->UpdateTime(visit_transfer_time);
  tasks_.push_back(std::make_shared<Task>(capacity - vehicle->remaining_capacity(),
                                          transfer->id(), max_time - vehicle->remaining_time()));
  vehicle->AddStop(transfer);
  vehicle->RestoreCapacity(capacity);
  return;
}

ZonePtr RoutesGenerator::SelectClosestTransferStation(int zone_id) {
  // if (zones.size() == 0) { return anchor; }
  double distance_first = instance_->GetDistance(zone_id, instance_->transfer_stations().first->id());
  double distance_second = instance_->GetDistance(zone_id, instance_->transfer_stations().second->id());
  if (distance_first <= distance_second) {
    return instance_->transfer_stations().first;
  }
  return instance_->transfer_stations().second;
}

bool RoutesGenerator::BelongsTo(ZonePtr zone, ZonePtrPair& zones) {
  return (zone == zones.first ? true : ((zone == zones.second) ? true : false));
}