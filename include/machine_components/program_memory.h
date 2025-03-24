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

#ifndef PROGRAM_MEMORY_H
#define PROGRAM_MEMORY_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../instructions/instruction.h"

class Instruction;
class RamMachine;

class ProgramMemory {
 public:
  ProgramMemory(RamMachine *machine);

  ~ProgramMemory() {}

  void ReadProgramInstructions(std::string &input_filename);

  int InstructionsQuantity() const { return this->instructions_set_.size(); }

  void ImprimeInstrucciones() {
    // std::cout << "Dentro de la memoria de programa encontramos lo siguiente:"
    //           << std::endl;
    // // for (int i{0}; i < instructions_set_.size(); ++i) {
    // //   std::cout << instructions_set_[i] << std::endl;
    // // }
    // std::cout << "Las etiquetas registradas son:" << std::endl;
    // for (auto i : this->labels_) {
    //   std::cout << i.first << " en línea " << i.second << "\n";
    // }
    // return;
  }

  unsigned CheckLabel(std::string label_to_check) const;

  Instruction *at(unsigned index) { return this->instructions_set_[index]; }

  int text_lines_counter() { return text_lines_counter_; }

 private:
  void ParseLine(std::string &line, int &instructions_index);
  std::string ExtractLabel(std::string line, int &instructions_index);
  Instruction *ClassifyInstruction(std::string code_line);
  std::vector<Instruction *> instructions_set_;
  std::map<std::string, int> labels_;
  RamMachine *machine_;
  int text_lines_counter_;
};

#endif