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



std::optional<ProgramOptions> ParseArguments(int argc, char* argv[]) {
  std::vector<std::string_view> args(argv + 1, argv + argc);
  ProgramOptions options;
  try {
    int arguments_counter{0};
    if (argc == 1) {
      throw std::invalid_argument("Not enough arguments provided!\n");
    }
    if (args[arguments_counter] == "-h" || args[arguments_counter] == "--help") {
      options.show_help = true;
      return options;
    }
    if (args[arguments_counter] == "-m" || args[arguments_counter] == "--multi") {
      options.multi_run = true;
      arguments_counter++;
    }
    options.instances_source = std::string(args[arguments_counter++]);
    if (args[arguments_counter++] == "-s") {
      options.grasp_size = std::stoi(std::string(args[arguments_counter++]));
    }
    else {
      throw std::invalid_argument("Expected -s (GRASP size)!");
    }
  }
  catch (const std::exception& error) {
    std::cerr << "\nError: " << error.what();
    PrintFile("./texts/usage.txt");
    return std::nullopt;
  }
  return options;
}

//       opciones.modo = std::string(args[++contador_argumentos]);
//       if (opciones.modo != "normal" && opciones.modo != "debug") {
//         throw std::invalid_argument("Modo no válido\n");
//       }
//       contador_argumentos++;
//       if (args[contador_argumentos] == "-a" |
//           args[contador_argumentos] == "--algoritmo") {
//         opciones.algoritmo = std::string(args[++contador_argumentos]);
//         std::string algoritmo = opciones.algoritmo;
//         if (algoritmo != "busqueda_binaria" && algoritmo != "hanoi" &&
//             algoritmo != "quicksort" && algoritmo != "mergesort") {
//           throw std::invalid_argument("Algoritmo no válido\n");
//         }
//         contador_argumentos++;
//         if (argc <= contador_argumentos) {
//           return std::nullopt;
//         }
//         if (opciones.modo == "debug") {
//           opciones.tamano_instancia =
//               std::stoi(std::string(args[contador_argumentos++]));
//         }
//       } else {
//         throw std::invalid_argument("Falta el argumento --a");
//       }
//     } else if (args[contador_argumentos] == "-h" ||
//                args[contador_argumentos] == "--help") {
//       opciones.mostrar_ayuda = true;
//       ImprimirArchivo("./texts/ayuda.txt");
//     } else if (args[contador_argumentos] != "-o" ||
//                args[contador_argumentos] == "--output") {
//       throw std::invalid_argument("Argumento no soportado.\n");
//     }
//     if (args[contador_argumentos] == "-o" ||
//         args[contador_argumentos] == "--output") {
//       opciones.imprimir_fichero = true;
//     }

//   return opciones;
// }


void PrintFile(const std::string& filename) {
  std::ifstream file{filename};
  if (file.is_open()) {
    std::cout << file.rdbuf();
  } else {
    std::cerr << "Error opening " << filename << '\n';
  }
  return;
}

std::vector<std::string> FilesInDirectory(const std::string& path) {
  namespace fs = std::filesystem;
  std::vector<std::string> paths_file;
  fs::path root_path = fs::absolute(path);
  fs::path execution_path = fs::current_path(); 

  if (!fs::exists(root_path) || !fs::is_directory(root_path)) {
    std::cerr << "Directory does not exist or is not valid.\n";
    return paths_file;
  }
  for (const auto& entrada : fs::directory_iterator(root_path)) {
    if (fs::is_regular_file(entrada.path())) {
      // Obtener ruta relativa desde el directorio de ejecución
      fs::path relative_path = fs::relative(entrada.path(), execution_path);
      paths_file.push_back("./" + relative_path.string());
    }
  }
  std::sort(paths_file.begin(), paths_file.end());
  return paths_file;
}

double ComputeEuclideanDistance(std::pair<int, int> first, std::pair<int, int> second) {
  double x_value = first.first - second.first;
  double y_value = first.second - second.second;
  return std::sqrt(std::pow(x_value, 2) + std::pow(y_value, 2));
}

int SpaceIndex(std::string& string_find) {
  int separator_index = string_find.find(" ");
  return separator_index;
}
  