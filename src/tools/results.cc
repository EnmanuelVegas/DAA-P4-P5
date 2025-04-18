/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file uitls.cc: Utility methods definitions for this project.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/tools/results.h"

#include <iomanip>  // Necesario para std::setprecision

void PrintHeader() {
  std::cout << std::endl << std::string(89, '-') << std::endl << "|";
  std::cout << CenterText("Instance") + "|";
  std::cout << CenterText("CV", 11) + "|";
  std::cout << CenterText("TV", 11) + "|";
  std::cout << CenterText("CV time") + "|";
  std::cout << CenterText("TV time") + "|";
  std::cout << CenterText("Total time") + "|";
  std::cout << CenterText("CPU_time") + "|";
  std::cout << std::endl << std::string(104, '-') << std::endl << "|";
  return;
}

void PrintSolutionSummary(std::vector<SolutionPtr>& solutions,
                          std::vector<std::string>& filenames) {
  PrintHeader();
  std::regex re("(instance\\d+)\\.txt");
  double cv_sum{0};
  double zones_sum{0};
  double tv_sum{0};
  double cv_time_sum{0};
  double tv_time_sum{0};
  double total_time_sum{0};
  double total_cpu_time{0};
  for (int i{0}; i < solutions.size(); i++) {
    std::string input_file = filenames[i];
    SolutionPtr solution = solutions[i];
    std::smatch match_name;
    std::regex_search(input_file, match_name, re);
    // Print Summary
    std::cout << CenterText(match_name[1].str()) + "|";
    std::cout << CenterText(std::to_string(solution->vehicles().size()), 11) + "|";
    std::cout << CenterText(
                     std::to_string(solution->transport_vehicles().size()), 11) + "|";
    std::cout << CenterText(std::to_string(solution->collection_time())) + "|";
    std::cout << CenterText(std::to_string(solution->transport_time())) + "|";
    std::cout << CenterText(std::to_string(solution->total_time())) + "|";
    std::cout << solution->CPU_time() << "|";
    std::cout << std::endl << "|";
    // Sum values
    cv_sum += solution->vehicles().size();
    tv_sum += solution->transport_vehicles().size();
    cv_time_sum += solution->collection_time();
    tv_time_sum += solution->transport_time();
    total_time_sum += solution->total_time();
    total_cpu_time += solution->CPU_time();
  }
  int instances_size = filenames.size();
  std::cout << std::string(89, '-') << std::endl << "|";
  std::cout << CenterText("Average") + "|";
  std::cout << CenterText(std::to_string(cv_sum / instances_size), 11) + "|";
  std::cout << CenterText(std::to_string(tv_sum / instances_size), 11) + "|";
  std::cout << CenterText(std::to_string(cv_time_sum / instances_size)) + "|";
  std::cout << CenterText(std::to_string(tv_time_sum / instances_size)) + "|";
  std::cout << CenterText(std::to_string(total_time_sum / instances_size)) + "|";
  std::cout << total_cpu_time / instances_size << "|";
  std::cout << std::endl << std::string(89, '-') << std::endl;
  return;
}
