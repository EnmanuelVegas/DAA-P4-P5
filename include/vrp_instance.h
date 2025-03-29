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

  // ZonePtr GetZone(int& index);

  std::vector<ZonePtr> collection_zones() { return collection_zones_; }
  
  int max_collection_time() { return this->max_collection_time_; }

  int max_transport_time() { return this->max_transport_time_; }

  int max_zones() { return this->max_zones_; }

  int collection_capacity() { return this->collection_capacity_; }

  int transport_capacity() { return this->transport_capacity_; }

  int speed() { return this->speed_; }

  ZonePtr depot() { return depot_; }

  ZonePtrPair transfer_stations() { return  transfer_stations_; }

  ZonePtr dumpsite() { return dumpsite_; }

double GetDistance(ZonePtr actual, int destination_id);

  double GetCollectionDistance(int zone_id, int collection_id);

  double GetTransferDistance(int zone_id, int transfer_id);

 private:

  void ReadZones(std::ifstream& filestream);
  void FillCollectionDistances();
  void FillTransferDistances();
  int max_collection_time_;
  int max_transport_time_;
  int max_vehicles_;
  int max_zones_;
  int collection_capacity_;
  int transport_capacity_;
  int speed_;
  std::vector<std::vector<int>> distances_collection_;
  std::vector<std::vector<int>> distances_transfer_;
  std::shared_ptr<Zone> depot_;
  std::shared_ptr<Zone> dumpsite_;
  std::vector<ZonePtr> collection_zones_;
  ZonePtrPair transfer_stations_;  
};

#endif