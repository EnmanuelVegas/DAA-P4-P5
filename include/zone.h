/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file zone.h
 * @brief Declaration of the `Zone` class.
 *
 * This file contains the definition of the `Zone` class, which represents
 * a zone in the context of the Vehicle Routing Problem (VRP).
 *
 * @date April 22, 2025
 */

 #ifndef ZONE_H
 #define ZONE_H
 
 #include <fstream>
 #include <iostream>
 #include <utility>
 
 #include "./tools/utils.h"
 
 class Zone;
 
 typedef std::pair<std::shared_ptr<Zone>, std::shared_ptr<Zone>> ZonePtrPair;
 
 typedef std::shared_ptr<Zone> ZonePtr;
 
 /**
  * @class Zone
  * @brief Represents a zone in the VRP.
  *
  * The `Zone` class contains information about a zone, such as its ID, coordinates,
  * waste quantity, and processing time.
  */
 class Zone {
  public:
   /**
    * @brief Default constructor for `Zone`.
    *
    * Initializes an empty zone.
    */
   Zone() {}
 
   /**
    * @brief Constructor for `Zone`.
    *
    * Initializes a zone with the given ID, coordinates, and demands.
    *
    * @param id The ID of the zone.
    * @param coordinates The coordinates of the zone.
    * @param demands The demands of the zone.
    */
   Zone(int id, std::pair<int, int> coordinates, std::pair<int, int> demands);
 
   /**
    * @brief Constructor for `Zone`.
    *
    * Initializes a zone with the given ID and input data.
    *
    * @param id The ID of the zone.
    * @param input The input data for the zone.
    */
   Zone(int id, std::string& input);
 
   /**
    * @brief Retrieves the waste quantity of the zone.
    *
    * @return The waste quantity.
    */
   double waste_quantity() { return waste_quantity_; }
 
   /**
    * @brief Retrieves the processing time of the zone.
    *
    * @return The processing time.
    */
   double process_time() { return process_time_; }
 
   /**
    * @brief Retrieves the ID of the zone.
    *
    * @return The ID of the zone.
    */
   int id() const { return this->id_; }
 
   /**
    * @brief Retrieves the coordinates of the zone.
    *
    * @return The coordinates of the zone.
    */
   std::pair<int, int> coordinates() const { return coordinates_; }
 
  protected:
   double process_time_;
   double waste_quantity_;
   std::pair<int, int> coordinates_;
   int id_;
 };
 
 #endif