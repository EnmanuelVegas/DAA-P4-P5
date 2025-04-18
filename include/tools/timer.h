/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file timer.h
 * @brief Declaration of the `Timer` class.
 *
 * This file contains the declaration of the `Timer` class, which provides
 * methods to measure execution time using a stopwatch mechanism.
 *
 * @date April 22, 2025
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

typedef std::chrono::steady_clock::time_point timestamp;

/**
* @class Timer
* @brief Class for measuring execution time.
*
* The `Timer` class provides methods to start and stop a stopwatch, and
* calculate the time difference between the start and end points.
*/
class Timer {
public:
  Timer() {}

  /**
  * @brief Starts the stopwatch.
  *
  * Records the current time as the start time.
  */
  void StartStopwatch();

  /**
  * @brief Stops the stopwatch and calculates the elapsed time.
  *
  * Records the current time as the end time and calculates the time difference
  * between the start and end points.
  *
  * @return The elapsed time in seconds.
  */
  double FinishStopwatch();

private:
  double CalculateTimeDifference();
  timestamp start_time_;
  timestamp finish_time_;
};

#endif