/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vrpt_main.cc: Programa cliente.
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
#include "../include/tools/timer.h"

int main(int argc, char* argv[]) {
  auto options_container = ParseArguments(argc, argv);
  if (!options_container) {
    return EXIT_FAILURE;
  }
  ProgramOptions options = options_container.value();
  if (options.show_help) {
    PrintFile("./texts/help.txt");
    return EXIT_SUCCESS;
  }
  try {
    std::vector<std::string> files{options.instances_source};
    if (options.multi_run) {
      files = FilesInDirectory(options.instances_source);
    }
    Timer chrono_timer = Timer();
    std::shared_ptr<VRPInstance> instance;
    std::shared_ptr<VRPTransshipments> solver;
    int grasp_size = options.grasp_size;
    for (auto& input_filename : files) {
      std::cout << "----------------------- File: " << input_filename << " -----------------------\n";
      instance = std::make_shared<VRPInstance>(input_filename);
      solver = std::make_shared<VRPTransshipments>(instance, grasp_size, 123);
      chrono_timer.StartStopwatch();
      solver->ComputeRoutes();
      std::cout << "-> Execution time: " << chrono_timer.FinishStopwatch() << " milliseconds\n";
    }
  } catch (const std::exception& error) {
    std::cerr << "An error has occurred: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
