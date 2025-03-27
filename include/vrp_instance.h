/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file greedy_vehicle_route.h: Declaracion de la clase 'GreedyVehicleRoute'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef VRP_INSTANCE_H
#define VRP_INSTANCE_H

#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <memory>

#include "zone.h"

typedef std::pair<std::shared_ptr<Zone>, std::shared_ptr<Zone>> ZonePtrPair;

typedef std::shared_ptr<Zone> ZonePtr;


/*
 * VRPT stands for Vehicle Routing Problem.
*/
class VRPInstance {
 public:
  VRPInstance(std::string& input_name);

  ZonePtr GetZone(int& index) { return zones_.at(index + 4); }
  
  int max_collection_time() { return this->max_collection_time_; }

  int max_transport_time() { return this->max_transport_time_; }

  int max_zones() { return this->max_zones_; }

  int collection_capacity() { return this->collection_capacity_; }

  int transport_capacity() { return this->transport_capacity_; }

  int speed() { return this->speed_; }

  ZonePtr depot() { return zones_.at(0); }

  ZonePtrPair transfer_stations() { return {zones_.at(1), zones_.at(2)}; }

  ZonePtr dumpsite() { return zones_.at(3); }

 private:

  void ReadZones(std::ifstream& filestream);
  void FillDistanceMatrix();
  int max_collection_time_;
  int max_transport_time_;
  int max_vehicles_;
  int max_zones_;
  int collection_capacity_;
  int transport_capacity_;
  int speed_;
  // std::shared_ptr<Zone> depot_;
  // std::shared_ptr<Zone> dumpsite_;
  std::vector<ZonePtr> zones_;
  // ZonePtrPair transfer_stations_;  
};

#endif