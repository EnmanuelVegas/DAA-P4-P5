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

#include "../../include/machine_components/program_memory.h"

#include <regex>

#include "../../include/instructions/add_instruction.h"
#include "../../include/instructions/div_instruction.h"
#include "../../include/instructions/halt_instruction.h"
#include "../../include/instructions/jump_greater_than_zero_instruction.h"
#include "../../include/instructions/jump_instruction.h"
#include "../../include/instructions/jump_zero_instruction.h"
#include "../../include/instructions/load_instruction.h"
#include "../../include/instructions/mul_instruction.h"
#include "../../include/instructions/read_instruction.h"
#include "../../include/instructions/store_instruction.h"
#include "../../include/instructions/sub_instruction.h"
#include "../../include/instructions/write_instruction.h"
#include "../../include/machine_components/ram_machine.h"
#include "../../include/tools/string_converter.h"

ProgramMemory::ProgramMemory(RamMachine* machine)
    : machine_(machine), text_lines_counter_(0) {
  std::cout << "- Creada ProgramMemory.\n";
  return;
}

/**
 * @brief Method to read and transform the strings from an input file into a set
 * of instructions.
 * @param Input file with the instructions
 */
void ProgramMemory::ReadProgramInstructions(std::string& input_filename) {
  std::ifstream input_file{input_filename};
  std::string line;
  if (input_file.is_open()) {
    int instructions_index{0};
    while (std::getline(input_file, line)) {
      try {
        this->ParseLine(line, instructions_index);
        ++this->text_lines_counter_;
      } catch (int error) {
        throw error;
      }
    }
  } else {
    throw 7;
  }
  this->text_lines_counter_ -= this->InstructionsQuantity();
  input_file.close();
  return;
}

/**
 * @brief Sets the line in order to be read by the programm memory
 * @param String whith the line and line number
 */
void ProgramMemory::ParseLine(std::string& line, int& instructions_index) {
  const std::regex kCommentPattern(R"(^\s*#.*$)");
  const std::regex kEmptyLinePattern(R"(^\s*$)");
  const std::regex kLabelPattern(R"(^.*:.*)");
  // Es una línea de comentarios. Ignoramos.
  if (std::regex_match(line, kCommentPattern) ||
      std::regex_match(line, kEmptyLinePattern)) {
    // ++text_lines_counter_ ;
    return;
  }
  // Es una línea que contiene una etiqueta.
  if (std::regex_match(line, kLabelPattern)) {
    // Nos quedamos con el resto de la línea
    line = ExtractLabel(line, instructions_index);
  }
  // Es una línea con solo una instrucción o alguna etiqueta fue extraída.
  size_t first = line.find_first_not_of("\t");
  if (first == std::string::npos) {
    return;
  }
  // Sería una línea vacía
  size_t last = line.find_last_not_of("\t");
  std::string clean_string = line.substr(first, (last - first + 1));
  Instruction* new_instruction;
  try {
    new_instruction = ClassifyInstruction(clean_string);
  } catch (int error) {
    throw error;
  }
  this->instructions_set_.push_back(new_instruction);
  ++instructions_index;
  return;
}

/**
 * @brief Registers a label on the list of known labels
 *
 * @param line where the label is allocated
 * @return Line without the label.
 */
std::string ProgramMemory::ExtractLabel(std::string line,
                                        int& instructions_index) {
  int end_of_label{0};
  for (int i{0}; i < line.size(); ++i) {
    if (line[i] == ':') {
      end_of_label = i;
    }
  }
  std::string label = line.substr(0, end_of_label);
  label.erase(std::remove(label.begin(), label.end(), ' '), label.end());
  labels_.insert(std::make_pair(label, instructions_index));
  line.erase(line.begin(), line.begin() + end_of_label + 1);
  return line;
}

/**
 * @brief Checks is a label is registered
 *
 * @param Label to check
 * @return position of the line where the label is allocated.
 */
unsigned ProgramMemory::CheckLabel(std::string label_to_check) const {
  for (auto i : labels_) {
    if (i.first == label_to_check) {
      return i.second;
    }
  }
  throw 0;
}

/**
 * @brief Classifies a given string in it's correspondant instruction type.
 *
 * @param String with the instruction
 * @return Pointer to a instruction
 */
Instruction* ProgramMemory::ClassifyInstruction(std::string code_line) {
  StringConverter converter = StringConverter();
  code_line = converter.StringToLowerCase(code_line);
  std::string instruction{""};
  std::string operand{""};
  bool white_space_found{false};
  for (int i{0}; i < code_line.size(); ++i) {
    if (code_line[i] == ' ') {
      white_space_found = true;
      continue;
    }
    if (!white_space_found) {
      instruction += code_line[i];
    } else {
      operand += code_line[i];
    }
  }
  if (instruction == "load") {
    return new LoadInstruction(operand, this->machine_->program_data());
  } else if (instruction == "store") {
    return new StoreInstruction(operand, this->machine_->program_data());
  } else if (instruction == "add") {
    return new AddInstruction(operand, this->machine_->program_data());
  } else if (instruction == "sub") {
    return new SubInstruction(operand, this->machine_->program_data());
  } else if (instruction == "mul") {
    return new MulInstruction(operand, this->machine_->program_data());
  } else if (instruction == "div") {
    return new DivInstruction(operand, this->machine_->program_data());
  } else if (instruction == "read") {
    return new ReadInstruction(operand, this->machine_->program_data());
  } else if (instruction == "write") {
    return new WriteInstruction(operand, this->machine_->program_data());
  } else if (instruction == "jump") {
    return new JumpInstruction(operand);
  } else if (instruction == "jzero") {
    return new JumpZeroInstruction(operand);
  } else if (instruction == "jgtz") {
    return new JumpGreaterThanZeroInstruction(operand);
  } else if (instruction == "halt") {
    return new HaltInstruction();
  }
  throw 5;
}