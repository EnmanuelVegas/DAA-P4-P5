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
#include <memory>

#include "../include/vrp_transshipments.h"
#include "../include/vrp_instance.h"


int main(int argc, char* argv[]) {
  try {
    std::string input_filename{argv[1]};
    std::shared_ptr<VRPInstance> instance = std::make_shared<VRPInstance>(input_filename);
    std::shared_ptr<VRPTransshipments> solver = std::make_shared<VRPTransshipments>(instance);
    solver->ComputeRoutes();

  } catch (const std::exception& error) {
    std::cerr << "Ha ocurrido un error: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
