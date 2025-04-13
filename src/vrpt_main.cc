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
    std::vector<std::string> files = GetFiles(options.instances_source);
    // Timer chrono_timer = Timer();
    std::shared_ptr<VRPInstance> instance;
    std::shared_ptr<VRPTransshipments> solver;
    int grasp_size = options.grasp_size;
    std::string result = "";
    result += CenterText("Instance", 15) + "|";
    result += CenterText("Nº vehicles", 15) + "|";
    result += CenterText("Best Time", 15) + "\n";
    result += std::string(45, '-') + "\n";
    SolutionPtr solution;
    std::regex re("(instance\\d+)\\.txt");
    int hola;
    for (auto& input_file : files) {
      // std::cout << "----------------------- File: " << input_file << " -----------------------\n";
      // std::cin >> hola;
      instance = std::make_shared<VRPInstance>(input_file);
      // solver = std::make_shared<VRPTransshipments>(instance, grasp_size, 123);
      solver = std::make_shared<VRPTransshipments>(instance, grasp_size);
      // chrono_timer.StartStopwatch();
      solution = solver->ComputeRoutes();
      std::smatch match_name;
      std::regex_search(input_file, match_name, re);  
      result += CenterText(match_name[1].str(), 15) + "|";
      result += CenterText(std::to_string(solution->vehicles().size()), 15) + "|";
      result += std::to_string(solution->total_time()) + "\n";
      // std::cout << "-> Execution time: " << chrono_timer.FinishStopwatch() << " milliseconds\n";
    }
    std::cout << result << std::endl;
  } catch (const std::exception& error) {
    std::cerr << "An error has occurred: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
