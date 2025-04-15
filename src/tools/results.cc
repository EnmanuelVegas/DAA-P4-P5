/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file uitls.cc: Utility methods definitions for this project.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/tools/results.h"

void PrintHeader() {
  std::cout << CenterText("Instance") + "|";
  // std::cout << CenterText("Nº zones", 15) + "|";
  std::cout << CenterText("CV", 11) + "|";
  std::cout << CenterText("TV", 11) + "|";
  std::cout << CenterText("CV time") + "|";
  std::cout << CenterText("TV time") + "|";
  std::cout << CenterText("Total time") + "|";
  std::cout << std::endl << std::string(80, '-') << std::endl;
  return;
}

void PrintSolutionSummary(std::vector<SolutionPtr>& solutions, std::vector<std::string>& filenames) {
  PrintHeader();
  std::regex re("(instance\\d+)\\.txt");
  double cv_sum{0};
  double zones_sum{0};
  double tv_sum{0};
  double cv_time_sum{0};
  double tv_time_sum{0};
  double total_time_sum{0};
  for (int i{0}; i < solutions.size(); i++) {
    // std::cout << "----------------------- File: " << input_file << " -----------------------\n";
    std::string input_file = filenames[i];
    SolutionPtr solution = solutions[i];
    std::smatch match_name;
    std::regex_search(input_file, match_name, re);  
    // Print Summary
    std::cout << CenterText(match_name[1].str()) + "|";
    // std::cout << CenterText(std::to_string(solution().size()), 15) + "|";
    std::cout << CenterText(std::to_string(solution->vehicles().size()), 11) + "|";
    std::cout << CenterText(std::to_string(solution->transport_vehicles().size()), 11) + "|";
    std::cout << CenterText(std::to_string(solution->total_time())) << std::endl;
    // std::cout << CenterText(std::to_string(solution->transport_vehicles().size())) + "|";
    // Sum values
    cv_sum += solution->vehicles().size();
    tv_sum += solution->transport_vehicles().size();
    cv_time_sum += solution->total_time();
  }
  int instances_size = filenames.size();
  std::cout << std::string(80, '-') << std::endl;
  std::cout << CenterText("Average") + "|";
  std::cout << CenterText(std::to_string(cv_sum / instances_size), 11) + "|";
  std::cout << CenterText(std::to_string(tv_sum / instances_size), 11) + "|";
  std::cout << CenterText(std::to_string(cv_time_sum / instances_size)) + "|";
  std::cout << CenterText(std::to_string(tv_time_sum / instances_size)) + "|";
  std::cout << std::endl << std::string(80, '-') << std::endl;
  return;
}


