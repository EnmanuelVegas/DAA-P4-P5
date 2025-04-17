/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Utility methods for this project.
 */

#ifndef RESULTS_H
#define RESULTS_H

#include <expected>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <regex>
#include <cmath>
#include <memory>

#include "./utils.h"
#include "../vrp_instance.h"
#include "../solution.h"

class Solution;

typedef std::shared_ptr<Solution> SolutionPtr;

void PrintSolutionSummary(std::vector<SolutionPtr>& solutions, std::vector<std::string>& filenames);

void PrintHeader();

#endif