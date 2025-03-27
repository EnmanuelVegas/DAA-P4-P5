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

#include <utility>
#include <cmath>
#include <string>

double ComputeEuclideanDistance(std::pair<int, int> first, std::pair<int, int> second);

int SpaceIndex(std::string& string_find);

#endif