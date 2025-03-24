/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file output_unit.h: Fichero de definición de métodos de la clase OutputFile.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Class to deal with the machine's input.
 * Ejecución: ./laberinto ./input/M1.txt output.txt
 */

#include "../../include/machine_components/output_unit.h"

#include <iostream>
#include <string>

/**
 * @brief Writes a value on the output tape
 *
 * @param Number to write
 */
void OutputUnit::Write(int integer_to_write) {
  output_file_ << integer_to_write << " ";
}