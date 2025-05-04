/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 * @file results.h
 * @brief Utility methods for handling and summarizing results.
 *
 * This file contains utility methods for processing and summarizing results
 * in the context of the Maximum Diversity Problem.
 *
 * @date  April 29, 2025
 */

#ifndef RESULTS_H
#define RESULTS_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <vector>

#include "../instance.h"
#include "../set_container.h"
#include "./utils.h"

struct Result {
  SetContainerPtr set_solution = nullptr;
  int input_size = 0;
  int LRC_size = 0;
  double CPU_time = 0;
  int generated_nodes = 0;
  std::string filename = "";
};

/**
 * @brief Prints a summary of the solutions.
 *
 * This function processes and prints a summary of the provided solutions
 * along with their corresponding filenames.
 *
 * @param solutions A vector of solutions to summarize.
 * @param filenames A vector of filenames corresponding to the solutions.
 */
void PrintSolutionSummary(std::vector<Result>& solutions);

/**
 * @brief Prints the header for the solution summary.
 *
 * This function prints the header used in the solution summary output.
 */
void PrintHeader(int table_width);

#endif