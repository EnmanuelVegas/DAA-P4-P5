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
      if (closest == nullptr) {
        break;
      }
      double return_depot_time = ReturnToDepotTime(last_stop, closest->id());
      // std::cout << return_depot_time << std::endl;
      if (closest->waste_quantity() <= current_vehicle->remaining_capacity() &&
          return_depot_time <= current_vehicle->remaining_time()) {
        current_vehicle->AddStop(closest);  // It also substracts the capacity.
        double visit_closest_time = CalculateTime(last_stop, closest->id());
        current_vehicle->UpdateTime(visit_closest_time);
        zones.erase(find(zones.begin(), zones.end(), closest));
      } else if (return_depot_time <= current_vehicle->remaining_time()) {
        ZonePtr closest_transfer = SelectClosestTransferStation(closest->id());
        current_vehicle->AddStop(closest_transfer);
        current_vehicle->RestoreCapacity(collection_capacity);
        double visit_transfer_time =
            CalculateTime(last_stop, closest_transfer->id());
        current_vehicle->UpdateTime(visit_transfer_time);
      } else {
        break;
      }
    }
    ZonePtr last_stop = current_vehicle->route().back();
    if (!BelongsTo(last_stop, transport_zones)) {
      ZonePtr closest_transport = SelectClosestTransferStation(last_stop->id());
      current_vehicle->AddStop(closest_transport);
      current_vehicle->AddStop(depot);
    } else {
      current_vehicle->AddStop(depot);
    }
    vehicles_used_.push_back(current_vehicle);
    std::cout << *(current_vehicle);
    vehicle_index++;
  }
  return this->vehicles_used_;
}

double RoutesGenerator::CalculateTime(ZonePtr actual, int destination_id) {
  return (instance_->GetDistance(actual->id(), destination_id) /
          instance_->speed()) *
         60;
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
  if (candidates.size() == 0) {
    return nullptr;
  }
  double minimum_distance{instance_->GetDistance(zone->id(), candidates[0]->id())};
  ZonePtr minimum_zone{candidates[0]};
  for (int i{0}; i < candidates.size(); i++) {
    int distance = instance_->GetDistance(zone->id(), candidates[i]->id());
    if (distance < minimum_distance && zone->id() != candidates[i]->id()) {
      minimum_distance = distance;
      minimum_zone = candidates[i];
    }
  }
  return minimum_zone;
}

ZonePtr RoutesGenerator::SelectClosestTransferStation(int zone_id) {
  // if (zones.size() == 0) { return anchor; }
  int distance_first = instance_->GetDistance(
      zone_id, instance_->transfer_stations().first->id());
  int distance_second = instance_->GetDistance(
      zone_id, instance_->transfer_stations().second->id());
  if (distance_first <= distance_second) {
    return instance_->transfer_stations().first;
  }
  return instance_->transfer_stations().second;
}

bool RoutesGenerator::BelongsTo(ZonePtr zone, ZonePtrPair& zones) {
  return (zone == zones.first ? true : ((zone == zones.second) ? true : false));
}