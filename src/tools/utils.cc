/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file uitls.cc: Utility methods definitions for this project.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/tools/utils.h"

std::optional<ProgramOptions> ParseArguments(int argc, char* argv[]) {
  std::vector<std::string_view> args(argv + 1, argv + argc);
  ProgramOptions options;
  try {
    int arguments_counter{0};
    if (argc == 1) {
      throw std::invalid_argument("Not enough arguments provided!\n");
    }
    if (args[arguments_counter] == "-h" ||
        args[arguments_counter] == "--help") {
      options.show_help = true;
      return options;
    }
    options.instances_source = std::string(args[arguments_counter++]);
    if (args[arguments_counter] == "-g" ||
        args[arguments_counter] == "-grasp") {
      arguments_counter++;
      options.grasp_size = std::stoi(std::string(args[arguments_counter++]));
    } else {
      throw std::invalid_argument("Expected -g (GRASP size)!");
    }
    if (args[arguments_counter] == "-m" ||
        args[arguments_counter] == "--multi") {
      options.multistart_quantity =
          std::stoi(std::string(args[++arguments_counter]));
    } else {
      throw std::invalid_argument("Expected -m (MULTISTART quantity)!");
    }
    if (options.grasp_size < 1 || options.multistart_quantity < 1) {
      throw std::invalid_argument("Arguments must be higher than 0!");
    }
  } catch (const std::exception& error) {
    std::cerr << "\nError: " << error.what();
    PrintFile("./texts/usage.txt");
    return std::nullopt;
  }
  return options;
}

void PrintFile(const std::string& filename) {
  std::ifstream file{filename};
  if (file.is_open()) {
    std::cout << file.rdbuf();
  } else {
    std::cerr << "Error opening " << filename << '\n';
  }
  return;
}

std::vector<std::string> GetFiles(const std::string& path) {
  namespace fs = std::filesystem;
  std::vector<std::string> files;
  fs::path root_path = fs::absolute(path);
  fs::path execution_path = fs::current_path();

  if (fs::is_regular_file(root_path)) {
    files.push_back(path);
    return files;
  }
  if (!fs::exists(root_path) || !fs::is_directory(root_path)) {
    std::cerr << "Directory does not exist or is not valid.\n";
    return files;
  }
  for (const auto& file : fs::directory_iterator(root_path)) {
    if (fs::is_regular_file(file.path())) {
      std::string filename = file.path().filename().string();
      fs::path relative_path = fs::relative(file.path(), execution_path);
      files.push_back(relative_path.string());
    }
  }
  std::sort(files.begin(), files.end());
  return files;
}

double ComputeEuclideanDistance(std::pair<int, int> first,
                                std::pair<int, int> second) {
  double x_value = first.first - second.first;
  double y_value = first.second - second.second;
  double distance = std::sqrt(std::pow(x_value, 2) + std::pow(y_value, 2));
  return RoundToFourDecimals(distance);
  // return distance;
}

bool IsLess(double a, double b, double epsilon) {
  return (b - a) > epsilon;
  // return (b - a) > 0;
}

double RoundToFourDecimals(double value) {
  return std::round(value * 10000.0) / 10000.0;
}

int SpaceIndex(std::string& string_find) {
  int separator_index = string_find.find(" ");
  return separator_index;
}