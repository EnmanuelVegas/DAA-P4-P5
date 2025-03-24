/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file main.cc: Programa cliente.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Contiene la función main del proyecto 'laberinto', que usa las clases
 * Maze y Node para gestionar la creación de objetos que permitan simular el
 * los algoritmos de Búsqueda A* para resolver un laberinto.
 * Compilación: makefile
 * Ejecución: ./laberinto ./input/M1.txt output.txt
 */

#include "../../include/machine_components/data_memory.h"

DataMemory::DataMemory()
    : indexed_registers_(std::vector<Register>(kRegisterQuantity)) {
  for (int i{0}; i < indexed_registers_.size(); i++) {
    this->indexed_registers_.at(i).value() = 0;
  }
  std::cout << "- Creada DataMemory." << std::endl;
}

void DataMemory::SetAccumulator(int new_value) {
  this->indexed_registers_[0].value() = new_value;
  return;
}