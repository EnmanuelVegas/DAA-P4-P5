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


std::vector<VehiclePtr> GreedyVehicleRoute::SolveAlgorithm(std::shared_ptr<VRPInstance> instance) {
  // Greedy Requirements
  std::vector<std::shared_ptr<Zone>> zones = instance->collection_zones();
  int collection_capacity = instance->collection_capacity();
  int max_time = instance->max_collection_time();
  ZonePtrPair transport_zones = instance->transfer_stations();
  ZonePtr depot = instance->depot();
  // Greedy start
  this->vehicles_used_.clear();
  int vehicle_index = 1;
  while (!zones.empty()) {
    VehiclePtr current_vehicle = std::make_shared<Vehicle>(vehicle_index, max_time, collection_capacity);
    current_vehicle->AddStop(depot);
    while (true) {
      ZonePtr last_stop = current_vehicle->route().back();
      ZonePtr closest = SelectClosestZone(last_stop, zones);
      int visit_closest_time = 0; // CALCULAR
      if (closest->waste_quantity() <= current_vehicle->remaining_capacity() &&
          visit_closest_time <= current_vehicle->remaining_time()) {
            current_vehicle->AddStop(closest); // It also substracts the capacity.
            // Update current_vehicle_time
            zones.erase(find(zones.begin(), zones.end(), closest));
      }
      else if (visit_closest_time <= current_vehicle->remaining_time()) {
        ZonePtr closest_transport = SelectClosestZone(closest, transport_zones);
        current_vehicle->AddStop(closest_transport); // It also substracts the capacity.
        // update capacity but to Q
        // Update current_vehicle_time
      }
      else {
        break;
      }
    }
    ZonePtr last_stop = vehicles_used_.back()->route().back();
    if (!BelongsTo(last_stop, transport_zones)) {
      ZonePtr closest_transport = SelectClosestZone(last_stop, transport_zones);
      current_vehicle->AddStop(closest_transport); // It also substracts the capacity.
      current_vehicle->AddStop(depot); // It also substracts the capacity.
    } else {
      current_vehicle->AddStop(depot); // It also substracts the capacity.
    }
    vehicles_used_.push_back(current_vehicle);
    vehicle_index++;
  }
  return this->vehicles_used_;
}

double GreedyVehicleRoute::CalculateTime(ZonePtr closest_zone, ZonePtrPair stations, ZonePtr depot) {
  
  return 0.0;
}


ZonePtr GreedyVehicleRoute::SelectClosestZone(ZonePtr zone, std::vector<ZonePtr>& candidates) {
  // if (zones.size() == 0) { return anchor; }
  int minimum_distance{0};
  int minimum_index{0};
  for (int i{0}; i < candidates.size(); i++) {
    int distance = ComputeEuclideanDistance(zone->coordinates(), candidates.at(i)->coordinates());
    if (distance < minimum_distance || zone != candidates.at(i)) {
      minimum_distance = distance;
      minimum_index = i;
    }
  }
  return candidates.at(minimum_index);
}

ZonePtr GreedyVehicleRoute::SelectClosestZone(ZonePtr zone, ZonePtrPair& transport_zones) {
  // int minimum_distance{0};
  int minimum_index{0};
  // for (int i{0}; i < candidates.size(); i++) {
  //   int distance = ComputeEuclideanDistance(zone->coordinates(), candidates.at(i)->coordinates());
  //   if (distance < minimum_distance) {
  //     minimum_distance = distance;
  //     minimum_index = i;
  //   }
  // }
  return transport_zones.first;
}



bool GreedyVehicleRoute::BelongsTo(ZonePtr zone, ZonePtrPair& zones) {
  return (zone == zones.first ? true : ((zone == zones.second) ? true : false));
}