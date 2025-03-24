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

#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H

#include <iostream>
#include <vector>

#include "register.h"

const int kRegisterQuantity = 32;

class DataMemory {
 public:
  DataMemory();

  std::vector<Register> indexed_registers() { return indexed_registers_; }

  void SetAccumulator(int new_value);

  const Register& Accumulator() const { return indexed_registers_[0]; }

  void Print() {
    std::cout << "\nRegistros: ";
    for (int i{0}; i < this->indexed_registers_.size(); i++) {
      std::cout << this->indexed_registers_[i].value() << ", ";
    }
    std::cout << std::endl;
  }

  int& at(int index) { return indexed_registers_[index].value(); }

  int at(int index) const { return indexed_registers_[index].value(); }

 private:
  std::vector<Register> indexed_registers_;
};

#endif