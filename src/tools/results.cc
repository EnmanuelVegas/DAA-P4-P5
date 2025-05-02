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

#include <iomanip>

void PrintHeader(int table_width) {
  std::cout << std::endl << std::string(table_width, '-') << std::endl << "|";
  std::cout << CenterText("Problem") + "|";
  std::cout << CenterText("n", 7) + "|";
  std::cout << CenterText("K", 7) + "|";
  std::cout << CenterText("m", 7) + "|";
  std::cout << CenterText("z", 11) + "|";
  std::cout << CenterText("S", 30) + "|";
  std::cout << CenterText("CPU_time", 11) + "|";
  std::cout << std::endl << std::string(table_width, '-') << std::endl << "|";
  return;
}

void PrintSolutionSummary(std::vector<Result>& solutions) {
  int table_width = 96;
  PrintHeader(table_width);
  std::regex re("(max_div_\\d+_\\d+)\\.txt");
  double distances_sum{0};
  double total_cpu_time{0};
  for (int i{0}; i < solutions.size(); i++) {
    Result result = solutions[i];
    std::string input_file = result.filename;
    std::smatch match_name;
    std::regex_search(input_file, match_name, re);
    // Print Summary
    std::cout << CenterText(match_name[1].str()) + "|";
    std::cout << CenterText(std::to_string(result.input_size), 7) + "|";
    std::cout << CenterText(std::to_string(result.set_solution->sets()[0]->Size()), 7) + "|";
    std::cout << CenterText(std::to_string(result.set_solution->sets().size()), 7) + "|";
    std::ostringstream distance_stream;
    distance_stream << std::fixed << std::setprecision(2) << result.set_solution->inner_distance();
    std::cout << CenterText(distance_stream.str(), 11) + "|";
    std::cout << CenterText(result.set_solution->ContainedIDs(), 30) + "|";
    std::cout << CenterText(std::to_string(result.CPU_time), 11) << "|";
    // Sum values
    distances_sum += result.set_solution->inner_distance();
    total_cpu_time += result.CPU_time;
    // Next line
    std::cout << std::endl << (((i + 1) % 4) ? "|" : std::string(table_width, '-') + "\n|") ;
  }
  int instances_size = solutions.size();
  std::cout << CenterText("Average") + "|";
  std::cout << CenterText("-", 7) + "|";
  std::cout << CenterText("-", 7) + "|";
  std::cout << CenterText("-", 7) + "|";
  std::cout << CenterText(std::to_string(distances_sum / instances_size), 11) + "|";
  std::cout << CenterText("-", 30) + "|";
  std::cout << CenterText(std::to_string(total_cpu_time / instances_size), 11) << "|";
  std::cout << std::endl << std::string(table_width, '-') << std::endl;
  return;
}
