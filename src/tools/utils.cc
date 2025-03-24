/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file uitls.cc: Utility methods definitions for this project.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/tools/utils.h"

/**
 * @brief Converts a string to lowercase
 *
 * @param String to convert
 * @return string converted to lowercase
 */
double ComputeEuclideanDistance(std::pair<int, int> first, std::pair<int, int> second) {
  double x_value = first.first - second.first;
  double y_value = first.second - second.second;
  return std::sqrt(std::pow(x_value, 2) + std::pow(y_value, 2));
}