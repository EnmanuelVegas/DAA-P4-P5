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


std::vector<Vehicle> GreedyVehicleRoute::SolveAlgorithm(std::shared_ptr<VRPInstance> instance) {
  std::vector<std::shared_ptr<Zone>> collection_zones = instance->zones();
  int collection_capacity = instance->collection_capacity();
  int max_time = instance->max_collection_time();
  ZonePtrPair transport_zones = instance->transfer_stations();
  
  this->vehicles_used_.clear();
  int vehicle_index = 1;
  while (!collection_zones.empty()) {
    Vehicle current_vehicle = Vehicle(vehicle_index, max_time, collection_capacity);
    current_vehicle.AddStop(depot);
    while (true) {
      Zone last_stop = vehicles_used_.back().route().back();
      std::shared_ptr<CollectionZone> closest = SelectClosestZone(last_stop, collection_zones);
      int visit_closest_time = 0; // CALCULAR
      if (closest.waste_quantity() <= current_vehicle.remaining_capacity() &&
          visit_closest_time <= current_vehicle.remaining_time()) {
            current_vehicle.AddStop(closest); // It also substracts the capacity.
            // Update current_vehicle_time
            collection_zones.erase(std::find(collection_zones.begin(), collection_zones.end(), closest));
      }
      else if (visit_closest_time <= current_vehicle.remaining_time()) {
        Zone closest_transport = SelectClosestZone(closest, transport_zones);
        current_vehicle.AddStop(closest_transport); // It also substracts the capacity.
        // update capacity but to Q
        // Update current_vehicle_time
      }
      else {
        break;
      }
    }
    Zone last_stop = vehicles_used_.back().route().back();
    if (!BelongsTo(last_stop, transport_zones)) {
      Zone closest_transport = SelectClosestZone(last_stop, transport_zones);
      current_vehicle.AddStop(closest_transport); // It also substracts the capacity.
      current_vehicle.AddStop(depot); // It also substracts the capacity.
    } else {
      current_vehicle.AddStop(depot); // It also substracts the capacity.
    }
    vehicles_used_.push_back(current_vehicle);
    vehicle_index++;
  }
  return this->vehicles_used_;
}


std::shared_ptr<CollectionZone> GreedyVehicleRoute::SelectClosestZone(
  std::shared_ptr<Zone> zone, std::vector<std::shared_ptr<Zone>>& candidates) {
  // if (zones.size() == 0) { return anchor; }
  int minimum_distance{0};
  int minimum_index{0};
  for (int i{0}; i < candidates.size(); i++) {
    int distance = ComputeEuclideanDistance(zone->coordinates(), candidates.at(i)->coordinates());
    if (distance < minimum_distance) {
      minimum_distance = distance;
      minimum_index = i;
    }
  }
  return std::dynamic_pointer_cast<CollectionZone>(candidates[minimum_index]);
}

bool GreedyVehicleRoute::BelongsTo(Zone zone, std::vector<Zone>& candidates) {
  for (int i{0}; i < candidates.size(); i++) {
    if (zone == candidates[i]) {
      return true;
    }
  }
  return false;
}