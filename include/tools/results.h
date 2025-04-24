// /**
//  * Universidad de La Laguna
//  * Escuela Superior de Ingeniería y Tecnología
//  * Grado en Ingeniería Informática
//  * Diseño y Análisis de Algoritmos (3º curso)
//  * @file results.h
//  * @brief Utility methods for handling and summarizing results.
//  *
//  * This file contains utility methods for processing and summarizing results
//  * in the context of the Maximum Diversity Problem.
//  *
//  * @date  April 29, 2025
//  */

// #ifndef RESULTS_H
// #define RESULTS_H

// #include <algorithm>
// #include <cmath>
// #include <fstream>
// #include <iostream>
// #include <memory>
// #include <regex>
// #include <vector>

// #include "../solution.h"
// #include "../vrp_instance.h"
// #include "./utils.h"

// class Solution;

// typedef std::shared_ptr<Solution> SolutionPtr;

// /**
//  * @brief Prints a summary of the solutions.
//  *
//  * This function processes and prints a summary of the provided solutions
//  * along with their corresponding filenames.
//  *
//  * @param solutions A vector of solutions to summarize.
//  * @param filenames A vector of filenames corresponding to the solutions.
//  */
// void PrintSolutionSummary(std::vector<SolutionPtr>& solutions,
//                           std::vector<std::string>& filenames);

// /**
//  * @brief Prints the header for the solution summary.
//  *
//  * This function prints the header used in the solution summary output.
//  */
// void PrintHeader(int table_width);

// #endif