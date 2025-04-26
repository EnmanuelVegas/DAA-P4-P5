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

#include "../include/element_set.h"
#include "../include/set_container.h"
#include "../include/solution_generator.h"
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
    std::vector<Result> solutions = std::vector<Result>(0);
    int grasp_size = options.grasp_size;
    int fixed_solution_size = options.solution_size;
    std::shared_ptr<Instance> instance;
    std::shared_ptr<SolutionGenerator> solver;
    Timer timer = Timer();
    for (auto& input_file : files) {
      std::cout << input_file << std::endl;
      for (int solution_size{2}; solution_size <= 5; solution_size++) {
        Result result = Result();
        timer.StartStopwatch();
        instance = std::make_shared<Instance>(input_file);
        solver = std::make_shared<SolutionGenerator>(instance, grasp_size, solution_size);  // 123, seed
        result.filename = input_file;
        result.input_size = instance->input_set()->Size();
        result.LRC_size = grasp_size;
        result.set_solution = solver->GenerateSolution();
        result.CPU_time = timer.FinishStopwatch();
        solutions.push_back(result);
      }
    }
    PrintSolutionSummary(solutions);
  } catch (const std::exception& error) {
    std::cerr << "An error has occurred: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
