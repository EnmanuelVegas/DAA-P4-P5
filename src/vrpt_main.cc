/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file crpt_main.cc: Programa cliente.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Contiene la función main del proyecto 'vrpt_main'.
 * Compilación: makefile
 * Ejecución: ./vrpt --help
 */

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
  try {
    std::string input_filename{argv[1]};
    
    // RamMachine ram_machine(instructions_filename, input_filename, output_file);
    // ram_machine.ExecuteProgram();
  } catch (const std::exception& error) {
    std::cerr << "Ha ocurrido un error: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
