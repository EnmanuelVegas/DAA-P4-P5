/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file main.cc: Programa cliente.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Definition of the methods from the class for managing input.
 * Ejecución: ./laberinto ./input/M1.txt output.txt
 */

#include "../../include/machine_components/input_unit.h"

#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief Class constructor
 *
 * @param Input file from which we want to read the data.
 */
InputUnit::InputUnit(const std::string &input_filename) : head_(0) {
  std::ifstream input_file{input_filename};
  if (input_file.is_open()) {
    std::string current_value{""};
    while (input_file >> current_value) {
      if (current_value != " ") {
        tape_.push_back(std::stoi(current_value));
      }
    }
  }
  else {
    throw 8;
  }
  std::cout << "- Creada InputUnit." << std::endl;
  return;
}

/**
 * @brief Method to read from the tape
 *
 * @return Value on the head position from the tape.
 */
int InputUnit::Read() {
  int result = tape_[head_];
  ++head_;
  return result;
}