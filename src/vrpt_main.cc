/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vrpt_main.cc: Programa cliente.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Contiene la función main del proyecto 'vrpt_main'.
 * Compilación: makefile
 * Ejecución: ./vrpt --help
 */

#include <iostream>
#include <memory>
#include <string>

#include "../include/solution_generator.h"
#include "../include/tools/results.h"
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
    std::vector<std::string> files = GetFiles(options.instances_source);
    std::vector<SolutionPtr> solutions = std::vector<SolutionPtr>(0);
    int grasp_size = options.grasp_size;
    int multistart_quantity = options.multistart_quantity;
    std::shared_ptr<VRPInstance> instance;
    std::shared_ptr<SolutionGenerator> solver;
    for (auto& input_file : files) {
      instance = std::make_shared<VRPInstance>(input_file);
      // std::cout << input_file << std::endl;
      // for (int i{0}; i < 3; i++) {
        solver = std::make_shared<SolutionGenerator>(instance, grasp_size, multistart_quantity); // 123, seed
        solutions.push_back(solver->GenerateSolution());
      // }
    }
    PrintSolutionSummary(solutions, files);
  } catch (const std::exception& error) {
    std::cerr << "An error has occurred: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
