/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vrp_instance.h
 * @brief Declaration of the `VRPInstance` class.
 *
 * This file contains the definition of the `VRPInstance` class, which represents
 * an instance of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

#ifndef VRP_INSTANCE_H
#define VRP_INSTANCE_H

#include <fstream>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "zone.h"

class VRPInstance;

typedef std::shared_ptr<VRPInstance> VRPInstancePtr;

/**
 * @class VRPInstance
 * @brief Represents an instance of the VRP.
 *
 * The `VRPInstance` class contains information about the problem instance, such as
 * zones, capacities, and distances.
 */
class VRPInstance {
 public:
  /**
  * @brief Constructor for `VRPInstance`.
  *
  * Initializes the VRP instance by reading data from the specified input file.
  *
  * @param input_name The name of the input file containing the VRP data.
  */
  VRPInstance(std::string& input_name);

  /**
   * @brief Retrieves the collection zones in the VRP instance.
   *
   * @return A vector of pointers to the collection zones.
   */
  std::vector<ZonePtr> collection_zones();

  /**
   * @brief Retrieves the maximum collection time allowed.
   *
   * @return The maximum collection time.
   */
  int max_collection_time() { return this->max_collection_time_; }

  /**
   * @brief Retrieves the maximum transport time allowed.
   *
   * @return The maximum transport time.
   */
  int max_transport_time() { return this->max_transport_time_; }

  /**
   * @brief Retrieves the maximum number of zones in the VRP instance.
   *
   * @return The maximum number of zones.
   */
  int max_zones() { return this->max_zones_; }

  /**
   * @brief Retrieves the collection capacity of the vehicles.
   *
   * @return The collection capacity.
   */
  int collection_capacity() { return this->collection_capacity_; }

  /**
   * @brief Retrieves the transport capacity of the vehicles.
   *
   * @return The transport capacity.
   */
  int transport_capacity() { return this->transport_capacity_; }

  /**
   * @brief Retrieves the speed of the vehicles.
   *
   * @return The speed of the vehicles.
   */
  int speed() { return this->speed_; }

  /**
   * @brief Retrieves the depot zone.
   *
   * @return A pointer to the depot zone.
   */
  ZonePtr depot() { return zones_[max_zones_]; }

  /**
   * @brief Retrieves the transfer stations in the VRP instance.
   *
   * @return A pair of pointers to the transfer stations.
   */
  ZonePtrPair transfer_stations();

  /**
   * @brief Retrieves a specific transfer station by its ID.
   *
   * @param id The ID of the transfer station.
   * @return A pointer to the transfer station.
   */
  ZonePtr single_transfer_station(int id);

  /**
   * @brief Retrieves the dumpsite zone.
   *
   * @return A pointer to the dumpsite zone.
   */
  ZonePtr dumpsite() { return zones_[max_zones_ + 3]; }


 /**
   * @brief Calculates the distance between two zones.
   *
   * @param actual_id The ID of the starting zone.
   * @param destination_id The ID of the destination zone.
   * @return The distance between the two zones.
   */
  double GetDistance(int actual_id, int destination_id);

  /**
   * @brief Calculates the time required to travel between two zones.
   *
   * @param actual_id The ID of the starting zone.
   * @param destination_id The ID of the destination zone.
   * @return The travel time between the two zones.
   */
  double CalculateTime(int actual_id, int destination_id);

  /**
   * @brief Checks if a given zone is a transfer station.
   *
   * @param zone A pointer to the zone to check.
   * @return true if the zone is a transfer station, false otherwise.
   */
  bool IsTransferStation(ZonePtr zone);

 private:
  /**
   * @brief Reads the zones from the input file.
   *
   * @param filestream The input file stream containing the zone data.
   */
  void ReadZones(std::ifstream& filestream);

  /**
   * @brief Computes the distances between all zones in the VRP instance.
   */
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