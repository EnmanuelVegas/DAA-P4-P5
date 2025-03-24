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

#ifndef RAM_MACHINE_H
#define RAM_MACHINE_H

#include <fstream>
#include <typeinfo>
#include <vector>

#include "../tools/machine_error.h"
#include "data_memory.h"
#include "input_unit.h"
#include "output_unit.h"
#include "program_memory.h"

class ProgramMemory;

class RamMachine {
 public:
  RamMachine(std::string &instructions_file, std::string &input_file,
             std::ofstream &output_file);

  ~RamMachine();

  void Imprimir();

  void ExecuteProgram();

  int ProgramCurrentLine();

  void UpdateProgramCounter(int new_program_counter);

  const ProgramMemory *program_instructions() const {
    return program_instructions_;
  }

  DataMemory *program_data() { return program_data_; }

  InputUnit *input_manager() { return input_manager_; }

  OutputUnit *output_manager() { return output_manager_; }

 private:
  DataMemory *program_data_;
  ProgramMemory *program_instructions_;
  InputUnit *input_manager_;
  OutputUnit *output_manager_;
  int program_counter_;
};

#endif