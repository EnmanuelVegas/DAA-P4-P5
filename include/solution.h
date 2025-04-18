/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file task.h: Declaracion de la clase 'Task'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef SOLUTION_H
#define SOLUTION_H

// #include <fstream>
#include <limits>

#include "./task.h"
#include "./collection_vehicle.h"
#include "./transport_vehicle.h"
#include "./vehicle.h"

class Solution;

typedef std::shared_ptr<Solution> SolutionPtr;

class Solution {
 public:
  Solution()
      : vehicles_(std::vector<CollectionVehiclePtr>(0)),
        transport_vehicles_(std::vector<TransportVehiclePtr>(0)),
        tasks_(std::vector<TaskPtr>(0)),
        total_time_(0),
        improvements_counter_(0) {}

  Solution(const Solution& other);

  Solution& operator=(const Solution& other);

  std::vector<CollectionVehiclePtr> vehicles() { return vehicles_; }

  std::vector<TransportVehiclePtr> transport_vehicles() {
    return transport_vehicles_;
  }

  void AssignTransportVehicles(std::vector<TransportVehiclePtr>& vehicles);

  double total_time() const { return this->total_time_; }

  // double collection_time() const { return this->collection_time_; }

  void UpdateTotalTime(double new_time) { total_time_ = new_time; }

  void UpdateTotalTime(int vehicle_id, VRPInstancePtr instance);

  int& improvements_counter() { return improvements_counter_; }

  bool IsRouteFeasible(int vehicle_id, VRPInstancePtr instance);

  void BuildTasks(VRPInstancePtr instance);

  bool IsBetter(SolutionPtr another);

  void PushVehicle(CollectionVehiclePtr vehicle);

  void PrintVehicleRoute(int vehicle_id);

  friend std::ostream& operator<<(std::ostream& os, const Solution& solution);

  std::vector<TaskPtr> tasks() { return tasks_; }

 protected:
  std::vector<CollectionVehiclePtr> vehicles_;
  std::vector<TransportVehiclePtr> transport_vehicles_;
  std::vector<TaskPtr> tasks_;
  double total_time_;
  int improvements_counter_;
};

#endif