/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file zone.h: Declaracion de la clase 'Zone'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#ifndef ZONE_H
#define ZONE_H

#include <fstream>
#include <utility>

class Zone {
 public:
  Zone(std::pair<int, int> coordinates) : coordinates_(coordinates) { }
  
  Zone() { }

  double waste_quantity() { return d2_ - d1_; }


  bool operator==(const Zone& other) const {
    return this->zone_id() == other.zone_id(); // Suponiendo que Zone tiene un atributo id
  }

  int zone_id() const { return this->zone_id_; }

  std::pair<int, int> coordinates() const { return coordinates_; }

  /**
  * @brief 'File Input' operator overloading to build a 'Zone' object.
  * @return std::ifstream input element.
  */
 friend std::ifstream& operator>>(std::ifstream& input_file, Zone& zone) {
  // std::ifstream& operator>>(std::ifstream& input, Automaton& automaton) {
  //   std::string line;
  //   std::getline(input, line);
  //   std::istringstream line_stream{line};
  //   char symbol_ascii;
  //   while (line_stream >> symbol_ascii) {
  //     automaton.automaton_associated_alphabet_.Insert(symbol_ascii);
  //   }
  //   int states_quantity;
  //   input >> states_quantity;
  //   input >> std::ws;  
  //   std::getline(input, line);
  //   line_stream.clear();
  //   line_stream.str(line);
  //   line_stream >> automaton.initial_state_;
  //   // We check there is only one starting state for the automaton
  //   if (line_stream >> automaton.initial_state_) {
  //     std::cout << "The automaton can only have ONE starting state. Check yout input!\n";
  //     exit (1);
  //   }
  //   // We do this to eliminate the left '\n' symbol after reading the first elements.
  //   input >> std::ws;
  //   automaton.ReadStates(input, states_quantity);
  //   return input;
  // }
 }

 private:
  int zone_id_;
  int d1_;
  int d2_;
  std::pair<int, int> coordinates_;
};

#endif