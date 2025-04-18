/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 * 
 * @file collection_vehicle.h
 * @brief Declaration of the `CollectionVehicle` class.
 *
 * This file contains the definition of the `CollectionVehicle` class, which
 * represents a collection vehicle in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

 #ifndef COLLECTION_VEHICLE_H
 #define COLLECTION_VEHICLE_H
 
 #include <fstream>
 #include <vector>
 
 #include "vehicle.h"
 
 class CollectionVehicle;
 
 typedef std::shared_ptr<CollectionVehicle> CollectionVehiclePtr;
 
 /**
  * @class CollectionVehicle
  * @brief Represents a collection vehicle in the VRP.
  *
  * The `CollectionVehicle` class inherits from `Vehicle` and provides functionality
  * specific to collection vehicles.
  */
 class CollectionVehicle : public Vehicle {
  public:
   /**
    * @brief Constructor for `CollectionVehicle`.
    *
    * Initializes a collection vehicle with the given ID, time, and capacity.
    *
    * @param id The ID of the vehicle.
    * @param time The maximum time available for the vehicle.
    * @param capacity The maximum capacity of the vehicle.
    */
   CollectionVehicle(int id = 0, int time = 0, int capacity = 0)
       : Vehicle(id, time, capacity) {}
 
   /**
    * @brief Copy constructor for `CollectionVehicle`.
    *
    * Creates a new `CollectionVehicle` by copying another instance.
    *
    * @param other The `CollectionVehicle` instance to copy.
    */
   CollectionVehicle(const CollectionVehicle& other);
 
   /**
    * @brief Assignment operator for `CollectionVehicle`.
    *
    * Assigns the values of another `CollectionVehicle` instance to this instance.
    *
    * @param other The `CollectionVehicle` instance to assign.
    * @return A reference to this `CollectionVehicle` instance.
    */
   CollectionVehicle& operator=(const CollectionVehicle& other);
  
   /**
    * @brief Overloads the output stream operator for `CollectionVehicle`.
    *
    * Outputs the details of the `CollectionVehicle` to the given stream.
    *
    * @param os The output stream.
    * @param vehicle The `CollectionVehicle` instance to output.
    * @return A reference to the output stream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const CollectionVehicle& vehicle);
 
  private:
 };
 
 #endif