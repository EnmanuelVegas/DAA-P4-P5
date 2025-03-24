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

#include "../../include/machine_components/ram_machine.h"

#include <iostream>

/**
 * @brief Constructor of the class
 *
 * @param Files from which we will take the program instructions, input and
 * output
 */
RamMachine::RamMachine(std::string &instructions_filename,
                       std::string &input_filename,
                       std::ofstream &output_file) {
  this->program_counter_ = 0;
  try {
    // IO units initialization.
    this->input_manager_ = new InputUnit(input_filename);
    this->output_manager_ = new OutputUnit(output_file);
    // Data and Memory initialization.
    this->program_data_ = new DataMemory();
    this->program_instructions_ = new ProgramMemory(this);

    this->program_instructions_->ReadProgramInstructions(instructions_filename);
  } catch (int error_code) {
    throw MachineError(error_code, ProgramCurrentLine());
  }
  std::cout << "- Se ha creado la Máquina RAM correctamente.\n" << std::endl;
  return;
}

/**
 * @brief shows the program line where the machine is on each moment
 *
 * @return Current program's line
 */
int RamMachine::ProgramCurrentLine() {
  return program_instructions_->text_lines_counter() + program_counter_ + 1;
}

/**
 * @brief Destructor of the class.
 */
RamMachine::~RamMachine() {
  delete this->program_data_;
  delete this->program_instructions_;
  delete this->output_manager_;
  delete this->input_manager_;
  return;
}

// void RamMachine::Imprimir() { program_instructions_->ImprimeInstrucciones();
// }

/**
 * @brief Method to run program's execution.
 */
void RamMachine::ExecuteProgram() {
  // this->Imprimir();
  std::cout << "Ejecutando programa...\n";
  while (program_counter_ < program_instructions_->InstructionsQuantity()) {
    try {
      this->program_instructions_->at(program_counter_)->Validate();
      std::cout << "Instrucción " << program_counter_ + 1 << ":\n";
      this->program_instructions_->at(program_counter_)->Execute(this);
      std::cout << "Después: ";
      this->program_data_->Print();
      ++program_counter_;
    } catch (int error_code) {
      throw MachineError(error_code, this->ProgramCurrentLine());
    }
  }
  std::cout << "Programa finalizado.\n" << std::endl;
  return;
}

/**
 * @brief Updates the program counter's position
 *
 * @param New value of the program counter
 */
void RamMachine::UpdateProgramCounter(int new_program_counter) {
  if (new_program_counter >
          this->program_instructions_->InstructionsQuantity() ||
      new_program_counter < 0) {
    throw 6;
  }
  std::cout << "\n" << new_program_counter << std::endl;
  --new_program_counter;
  std::cout << "\n" << new_program_counter << std::endl;
  this->program_counter_ = new_program_counter;
  return;
}