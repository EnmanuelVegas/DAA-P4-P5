/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 * @file utils.h
 * @brief Utility methods for this project.
 *
 * This file contains utility functions and structures used throughout the
 * project, including mathematical operations, file handling, and text
 * formatting.
 *
 * @date  April 29, 2025
 */

#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <expected>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <string_view>
#include <vector>

constexpr double kEpsilon = 1e-5;

/**
 * @struct ProgramOptions
 * @brief Represents the program options parsed from the command line.
 *
 * Contains flags and parameters such as help display, source file paths, and
 * algorithm settings.
 */
struct ProgramOptions {
  bool show_help{false};
  bool apply_local_search{false};
  bool apply_byb{false};
  std::string instances_source{""};
  std::string algorithm{""};
  int grasp_size{0};
};

/**
 * @brief Parses command-line arguments into program options.
 *
 * This function processes the command-line arguments and extracts the program
 * options.
 *
 * @param argc The number of arguments.
 * @param argv The array of argument strings.
 * @return An optional `ProgramOptions` structure containing the parsed options.
 */
std::optional<ProgramOptions> ParseArguments(int argc, char* argv[]);

/**
 * @brief Prints the contents of a file to the standard output.
 *
 * This function reads the specified file and outputs its contents to the
 * console.
 *
 * @param filename The name of the file to print.
 */
void PrintFile(const std::string& filename);

/**
 * @brief Retrieves a list of files from a specified directory.
 *
 * This function scans the given directory and returns a vector of file names.
 *
 * @param path The path to the directory.
 * @return A vector of file names in the directory.
 */
std::vector<std::string> GetFiles(const std::string& path);

/**
 * @brief Centers a given text within a specified width.
 *
 * This inline lambda function takes a string and centers it within the
 * specified width by adding padding spaces on both sides.
 *
 * @param text The text to center.
 * @param width The total width for centering the text.
 * @return A string with the centered text.
 */
inline auto CenterText = [](const std::string& text, int width = 15) {
  int padding = width - text.size();
  int left_padding = padding / 2;
  int right_padding = padding - left_padding;
  return std::string(left_padding, ' ') + text +
         std::string(right_padding, ' ');
};

/**
 * @brief Compares two floating-element numbers with a tolerance.
 *
 * This function checks if the first number is less than the second number,
 * considering a small tolerance value to account for floating-element precision
 * errors.
 *
 * @param a The first number.
 * @param b The second number.
 * @param epsilon The tolerance value (default is `kEpsilon`).
 * @return true if `a` is less than `b` within the tolerance, false otherwise.
 */
bool IsGreater(double a, double b, double epsilon = kEpsilon);

/**
 * @brief Rounds a floating-element number to Two decimal places.
 *
 * This function rounds the given number to Two decimal places using standard
 * rounding rules.
 *
 * @param value The number to round.
 * @return The rounded number.
 */
double RoundToTwoDecimals(double value);

/**
 * @brief Computes the Euclidean distance between two elements.
 *
 * This function calculates the Euclidean distance between two elements
 * represented as pairs of integers.
 *
 * @param first The coordinates of the first element.
 * @param second The coordinates of the second element.
 * @return The Euclidean distance between the two elements.
 */
double ComputeEuclideanDistance(std::vector<double> first, std::vector<double> second);

/**
 * @brief Finds the index of the first space in a string.
 *
 * This function searches for the first occurrence of a space character in the
 * given string and returns its index.
 *
 * @param string_find The string to search.
 * @return The index of the first space, or -1 if no space is found.
 */
int SpaceIndex(std::string& string_find);

#endif