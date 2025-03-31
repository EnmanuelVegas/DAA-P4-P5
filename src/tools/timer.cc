/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file timer.cc: Fichero de definición de métodos de la clase Timer.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Contiene la definición de los métodos de la clase Timer.
 */

#include "../../include/tools/timer.h"

void Timer::StartStopwatch() {
  this->start_time_ = std::chrono::steady_clock::now();
}

double Timer::FinishStopwatch() {
  this->finish_time_ = std::chrono::steady_clock::now();
  return CalculateTimeDifference();
}

double Timer::CalculateTimeDifference() {
  double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish_time_ - start_time_).count();
  // return elapsed * kSecondsTransformator;
  return elapsed;
}