/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.h: Declaracion de la clase 'CollectionVehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef COLLECTION_VEHICLE_H
#define COLLECTION_VEHICLE_H

#include <fstream>
#include <vector>

#include "vehicle.h"

class CollectionVehicle;

typedef std::shared_ptr<CollectionVehicle> CollectionVehiclePtr;

class CollectionVehicle : public Vehicle {
 public:
  CollectionVehicle(int id = 0, int time = 0, int capacity = 0)
      : Vehicle(id, time, capacity) { }

  CollectionVehicle(const CollectionVehicle& other);

  CollectionVehicle& operator=(const CollectionVehicle& other);
  int prueba() { return 1;}

  friend std::ostream& operator<<(std::ostream& os, const CollectionVehicle& vehicle);

 private:

};

#endif