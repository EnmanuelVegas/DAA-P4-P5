/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Utility methods for this project.
 */

#ifndef UTILS_H
#define UTILS_H

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

constexpr double kEpsilon = 1e-9;


struct ProgramOptions {
  bool show_help{false};
  bool multi_run{false};
  std::string instances_source{""};
  // bool imprimir_fichero = false;
  int grasp_size{0};
  // std::string algoritmo = "quicksort";
};

std::optional<ProgramOptions> ParseArguments(int argc, char* argv[]);

void PrintFile(const std::string& filename);

std::vector<std::string> GetFiles(const std::string& path);

inline auto CenterText = [](const std::string& text, int width) {
  int padding = width - text.size();
  int left_padding = padding / 2;
  int right_padding = padding - left_padding;
  return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
};

double ComputeEuclideanDistance(std::pair<int, int> first, std::pair<int, int> second);

int SpaceIndex(std::string& string_find);

#endif