/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.h: Declaracion de la clase 'GreedyVehicleRoute'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include <fstream>
#include <vector>

#include "../include/greedy_vehicle_route.h"


std::vector<VehiclePtr> GreedyVehicleRoute::SolveAlgorithm() {
  // Greedy Requirements
  std::vector<ZonePtr> zones = instance_->collection_zones();
  int collection_capacity = instance_->collection_capacity();
  int max_time = instance_->max_collection_time();
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
      int return_depot_time = ReturnToDepotTime(last_stop, closest->id());
      if (closest->waste_quantity() <= current_vehicle->remaining_capacity() &&
          return_depot_time <= current_vehicle->remaining_time()) {
            current_vehicle->AddStop(closest); // It also substracts the capacity.
            double visit_closest_time = CalculateTime(last_stop, closest->id()); 
            zones.erase(find(zones.begin(), zones.end(), closest));
      }
      else if (return_depot_time <= current_vehicle->remaining_time()) {
        ZonePtr closest_transfer = SelectClosestTransferStation(closest->id());
        current_vehicle->AddStop(closest_transfer);
        current_vehicle->RestoreCapacity(collection_capacity);
        double visit_transfer_time = CalculateTime(last_stop, closest_transfer->id()); 
      }
      else {
        break;
      }
    }
    ZonePtr last_stop = vehicles_used_.back()->route().back();
    if (!BelongsTo(last_stop, transport_zones)) {
      ZonePtr closest_transport = SelectClosestTransferStation(last_stop->id());
      current_vehicle->AddStop(closest_transport);
      current_vehicle->AddStop(depot);
    } else {
      current_vehicle->AddStop(depot);
    }
    vehicles_used_.push_back(current_vehicle);
    vehicle_index++;
  }
  return this->vehicles_used_;
}

double GreedyVehicleRoute::CalculateTime(ZonePtr actual, int destination_id) {
  return (instance_->GetDistance(actual, destination_id) / instance_->speed());
}

double GreedyVehicleRoute::ReturnToDepotTime(ZonePtr actual_zone, int closest_id) {
  // dist_1 = Current zone to closest collection zone.
  double dist_1 = instance_->GetDistance(actual_zone, closest_id);
  ZonePtr transfer = SelectClosestTransferStation(closest_id);
  // dist_2 = closest collection to closest SWTS.
  double dist_2 = instance_->GetTransferDistance(closest_id, transfer->id());
  // dist_3 = SWTS to depot.
  double dist_3 = ComputeEuclideanDistance(instance_->depot()->coordinates(), transfer->coordinates());
  int speed = instance_->speed();
  // time = distance / speed
  return ((dist_1 + dist_2 + dist_3) / speed);
}

ZonePtr GreedyVehicleRoute::SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates) {
  // if (zones.size() == 0) { return anchor; }
  double minimum_distance{instance_->GetDistance(zone, candidates[0]->id())};
  ZonePtr minimum_zone{candidates[0]};
  for (int i{0}; i < candidates.size(); i++) {
    int distance = instance_->GetDistance(zone, candidates[i]->id());
    if (distance < minimum_distance && zone->id() != candidates[i]->id()) {
      minimum_distance = distance;
      minimum_zone = candidates[i];
    }
  }
  return minimum_zone;
}

ZonePtr GreedyVehicleRoute::SelectClosestTransferStation(int zone_id) {
  // if (zones.size() == 0) { return anchor; }
  if (instance_->GetTransferDistance(zone_id, -1) <= 
      instance_->GetTransferDistance(zone_id, -2)) {
    return instance_->transfer_stations().first;
  }
  return instance_->transfer_stations().second;
}

bool GreedyVehicleRoute::BelongsTo(ZonePtr zone, ZonePtrPair& zones) {
  return (zone == zones.first ? true : ((zone == zones.second) ? true : false));
}