/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file main.cc: Programa cliente.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es), Diego Hernández Chico
 * @brief Class to deal with the machine's input.
 * Ejecución: ./laberinto ./input/M1.txt output.txt
 */

#include <fstream>
#include <vector>

#ifndef INPUT_UNIT_H
#define INPUT_UNIT_H

class InputUnit {
 public:
  InputUnit() {}
  InputUnit(const std::string &input_filename);
  int Read();

 private:
  int head_;
  std::vector<int> tape_;
};

#endif