/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file output_unit.h: Fichero de declaración de la clase OutputFile.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Class to deal with the machine's input.
 * Ejecución: ./laberinto ./input/M1.txt output.txt
 */

#include <fstream>
#include <vector>
#include <iostream>

#ifndef OUTPUT_UNIT_H
#define OUTPUT_UNIT_H

class OutputUnit {
 public:
  OutputUnit(std::ofstream &output_file) : output_file_(output_file) { 
    std::cout << "- Creada OutputUnit." << std::endl;
  }

  void Write(int integer_to_write);

 private:
  std::ofstream &output_file_;
};

#endif