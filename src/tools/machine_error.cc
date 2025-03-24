/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Definition of the class to represent error handling in the RamMachine
 * Class.
 */

#include "../../include/tools/machine_error.h"

#include <string>

MachineError::MachineError(int error_code, int program_line) {
  switch (error_code) {
    case 0:
      error_message_ = "Acceso a etiqueta inválida";
      break;
    case 1:
      error_message_ =
          "Acceso a registro inexistente mediante direccionamiento directo"
          "(Ri, i >= 32 | i < 0)";
      break;
    case 2:
      error_message_ =
          "Acceso a registro inexistente mediante direccionamiento indirecto "
          "(Ri, i >= 32 | i < 0)";
      break;
    case 3:
      error_message_ = "La instrucción no admite a R0 como operando";
      break;
    case 4:
      error_message_ = "La instrucción no admite una constante como operando";
      break;
    case 5:
      error_message_ = "Se ha introducido una instrucción inválida";
      break;
    case 6:
      error_message_ = "Posición del program counter inválida";
      break;
    case 7:
      error_message_ =
          "Archivo de instrucciones de programa no válido/encontrado";
      break;
    case 8:
      error_message_ = "Archivo de input de programa no válido/encontrado";
      break;
    default:
      error_message_ = "Error general.";
      break;
  }
  if (error_code > 6) {
    return;
  }
  error_message_ += ". En la línea ";
  error_message_ += std::to_string(program_line);
  return;
}
