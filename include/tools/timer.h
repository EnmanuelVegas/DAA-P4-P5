/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file timer.h: Fichero de declaración de la clase Timer.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @brief Contiene la declaración de los métodos de la clase Timer.
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Constante para transformar nanosegundos a segundos.
// const double kSecondsTransformator = 1e-9; 

// Tipo para representar puntos en el tiempo.
typedef std::chrono::steady_clock::time_point timestamp;

/**
 * @class Timer
 * @brief Clase para medir el tiempo de ejecución.
 *
 * Esta clase proporciona métodos para iniciar y detener un cronómetro, y calcular
 * la diferencia de tiempo entre el inicio y el fin.
 */
class Timer {
 public:
  
  Timer() { }
  
  /**
   * @brief Inicia el cronómetro.
   * Guarda el tiempo actual como el tiempo de inicio.
   */  
  void StartStopwatch();

  /**
   * @brief Detiene el cronómetro y calcula el tiempo transcurrido.
   * Guarda el tiempo actual como el tiempo de fin y calcula la diferencia de tiempo
   * entre el inicio y el fin.
   * @return El tiempo transcurrido en segundos.
   */
  double FinishStopwatch();

 private:
  double CalculateTimeDifference();
  timestamp start_time_;
  timestamp finish_time_;
};

#endif