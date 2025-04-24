// /**
//  * Universidad de La Laguna
//  * Escuela Superior de Ingeniería y Tecnología
//  * Grado en Ingeniería Informática
//  * Diseño y Análisis de Algoritmos (3º curso)
//  *
//  * @file uitls.cc: Utility methods definitions for this project.
//  * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
//  */

// #include "../../include/tools/results.h"

// #include <iomanip>  // Necesario para std::setprecision

// void PrintHeader(int table_width) {
//   std::cout << std::endl << std::string(table_width, '-') << std::endl << "|";
//   std::cout << CenterText("Instance") + "|";
//   std::cout << CenterText("CV", 11) a "|";
//   std::cout << CenterText("TV", 11) + "|";
//   std::cout << CenterText("CV time") + "|";
//   std::cout << CenterText("TV time") + "|";
//   std::cout << CenterText("Total time") + "|";
//   std::cout << CenterText("CPU_time", 13) + "|";
//   std::cout << std::endl << std::string(table_width, '-') << std::endl << "|";
//   return;
// }

// void PrintSolutionSummary(std::vector<SolutionPtr>& solutions,
//                           std::vector<std::string>& filenames) {
//   int table_width = 103;
//   PrintHeader(table_width);
//   std::regex re("(instance\\d+)\\.txt");
//   double cv_sum{0};
//   double zones_sum{0};
//   double tv_sum{0};
//   double cv_time_sum{0};
//   double tv_time_sum{0};
//   double total_time_sum{0};
//   double total_cpu_time{0};
//   for (int i{0}; i < filenames.size(); i++) {
//   // for (int j{0}; j < 3; ++j) {
//     std::string input_file = filenames[i];
//     SolutionPtr solution = solutions[i];
//     // SolutionPtr solution = solutions[i * 3 + j];
//     std::smatch match_name;
//     std::regex_search(input_file, match_name, re);
//     // Print Summary
//     std::cout << CenterText(match_name[1].str()) + "|";
//     std::cout << CenterText(std::to_string(solution->vehicles().size()), 11) + "|";
//     std::cout << CenterText(std::to_string(solution->transport_vehicles().size()), 11) + "|";
//     std::cout << CenterText(std::to_string(solution->collection_time())) + "|";
//     std::cout << CenterText(std::to_string(solution->transport_time())) + "|";
//     std::cout << CenterText(std::to_string(solution->total_time())) + "|";
//     std::cout << CenterText(std::to_string(solution->CPU_time()), 13) << "|";
//     std::cout << std::endl << "|";
//     // Sum values
//     cv_sum += solution->vehicles().size();
//     tv_sum += solution->transport_vehicles().size();
//     cv_time_sum += solution->collection_time();
//     tv_time_sum += solution->transport_time();
//     total_time_sum += solution->total_time();
//     total_cpu_time += solution->CPU_time();
//   // }
//   }
//   int instances_size = solutions.size();
//   std::cout << std::string(table_width, '-') << std::endl << "|";
//   std::cout << CenterText("Average") + "|";
//   std::cout << CenterText(std::to_string(cv_sum / instances_size), 11) + "|";
//   std::cout << CenterText(std::to_string(tv_sum / instances_size), 11) + "|";
//   std::cout << CenterText(std::to_string(cv_time_sum / instances_size)) + "|";
//   std::cout << CenterText(std::to_string(tv_time_sum / instances_size)) + "|";
//   std::cout << CenterText(std::to_string(total_time_sum / instances_size)) + "|";
//   std::cout << CenterText(std::to_string(total_cpu_time / instances_size), 13) << "|";
//   std::cout << std::endl << std::string(table_width, '-') << std::endl;
//   return;
// }
