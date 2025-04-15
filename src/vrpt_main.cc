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

#include "../include/tools/timer.h"
#include "../include/tools/results.h"

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
    std::vector<std::string> files = GetFiles(options.instances_source);
    std::vector<SolutionPtr> solutions = std::vector<SolutionPtr>(0);
    int grasp_size = options.grasp_size;
    std::shared_ptr<VRPInstance> instance;
    std::shared_ptr<VRPTransshipments> solver;
    for (auto& input_file : files) {
      instance = std::make_shared<VRPInstance>(input_file);
      solver = std::make_shared<VRPTransshipments>(instance, grasp_size);
      // chrono_timer.StartStopwatch();
      solutions.push_back(solver->ComputeRoutes());
      // std::cout << "-> Execution time: " << chrono_timer.FinishStopwatch() << " milliseconds\n";


    }
    PrintSolutionSummary(solutions, files);
  } catch (const std::exception& error) {
    std::cerr << "An error has occurred: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
