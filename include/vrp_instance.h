/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file routes_generator.h: Declaracion de la clase 'RoutesGenerator'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef VRP_INSTANCE_H
#define VRP_INSTANCE_H

#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>

#include "zone.h"

class VRPInstance;

typedef std::shared_ptr<VRPInstance> VRPInstancePtr;

/*
 * VRPT stands for Vehicle Routing Problem.
 */
class VRPInstance {
 public:
  VRPInstance(std::string& input_name);

  std::vector<ZonePtr> collection_zones();

  int max_collection_time() { return this->max_collection_time_; }

  int max_transport_time() { return this->max_transport_time_; }

  int max_zones() { return this->max_zones_; }

  int collection_capacity() { return this->collection_capacity_; }

  int transport_capacity() { return this->transport_capacity_; }

  int speed() { return this->speed_; }

  ZonePtr depot() { return zones_[max_zones_]; }

  ZonePtrPair transfer_stations();

  ZonePtr dumpsite() { return zones_[max_zones_ + 3]; }

  double GetDistance(int actual_id, int destination_id);

  double CalculateTime(int actual_id, int destination_id);

  bool IsTransferStation(ZonePtr zone);

 private:
  void ReadZones(std::ifstream& filestream);
  void ComputeDistances();
  int max_collection_time_;
  int max_transport_time_;
  int max_vehicles_;
  int max_zones_;
  int collection_capacity_;
  int transport_capacity_;
  int speed_;
  std::vector<std::vector<double>> distances_;
  std::shared_ptr<Zone> depot_;
  std::shared_ptr<Zone> dumpsite_;
  std::vector<ZonePtr> zones_;
  ZonePtrPair transfer_stations_;
};

#endif