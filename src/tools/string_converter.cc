/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file main.cc: Programa cliente.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Contiene la función main del proyecto 'laberinto', que usa las clases
 * Maze y Node para gestionar la creación de objetos que permitan simular el
 * los algoritmos de Búsqueda A* para resolver un laberinto.
 * Compilación: makefile
 * Ejecución: ./laberinto ./input/M1.txt output.txt
 */

#include "../../include/tools/string_converter.h"

/**
 * @brief Converts a string to lowercase
 *
 * @param String to convert
 * @return string converted to lowercase
 */
std::string StringConverter::StringToLowerCase(std::string &original_string) {
  std::string lower_case_string = original_string;
  std::transform(lower_case_string.begin(), lower_case_string.end(),
                 lower_case_string.begin(), ::tolower);
  return lower_case_string;
}