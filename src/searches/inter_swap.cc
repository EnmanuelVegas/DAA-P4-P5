/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos (3º curso)
 *
 * @file vehicle.cc: Definición de métodos de la clase 'Vehicle'.
 * @author Enmanuel Vegas (alu0101281698@ull.edu.es)
 */

#include "../../include/searches/inter_swap.h"

#include <iomanip>

std::pair<bool, SetContainerPtr> InterSwap::GetBestNeighbor(
        SetContainerPtr solution, SetContainerPtr candidates) {
//   // // std::cout << *solution;
//   // // std::cout << "Entrada InterSwap" << std::endl;
//   // double best_neighbor_time = solution->total_time();
//   // int vehicles_size{int(solution->vehicles().size())};
//   // for (int i{0}; i < vehicles_size; i++) {
//   //   auto vehicle = solution->vehicles()[i];
//   //   int route_size{int(vehicle->route().size())};
//   //   for (int k{1}; k < route_size - 1; k++) {
//   //     for (int l{i + 1}; l < vehicles_size; l++) {
//   //       auto other_vehicle = solution->vehicles()[l];
//   //       int other_route_size{int(other_vehicle->route().size())};
//   //       for (int m{1}; m < other_route_size - 1; m++) {
//   //         if ((instance->IsTransferStation(vehicle->route()[k])) ||
//   //             (instance->IsTransferStation(other_vehicle->route()[m]))) {
//   //           continue;
//   //         }
//   //         // std::cout << "Movimiento: Vehiculo " << i + 1 << ", otro " << l + 1
//   //         // << ", first: " << vehicle->route()[k]->id() << ", second:" <<
//   //         // other_vehicle->route()[m]->id() << std::endl;
//   //         InterSwapMovement candidate = {vehicle->id(), other_vehicle->id(), k,
//   //                                        m};
//   //         InterSwapTimes new_times = GetNewTime(solution, candidate, instance);
//   //         // std::cout << "De nuevo en bucle grande" << std::endl;
//   //         if (!(IsLess(new_times.whole_time, best_neighbor_time))) {
//   //           continue;
//   //         }
//   //         if (IsLegalMovement(solution, new_times, instance)) {
//   //           // std::cout << "CANDIDATO: Vehiculo " << i + 1 << ", otro " << l +
//   //           // 1 << ", first: " << vehicle->route()[k]->id() << ", second:" <<
//   //           // other_vehicle->route()[m]->id() << std::endl;
//   //           movement_ = candidate;
//   //           best_neighbor_time = new_times.whole_time;
//   //         }
//   //       }
//   //     }
//   //   }
//   // }
//   // if (IsLess(best_neighbor_time, solution->total_time())) {
//   //   // std::cout << "Del vehículo " << movement_.first_vehicle_id << " con
//   //   // vehiculo "
//   //   // << movement_.second_vehicle_id << " swap de " <<
//   //   // solution->vehicles()[movement_.first_vehicle_id -
//   //   // 1]->route()[movement_.first_route_zone_id]->id()
//   //   //  << " con " << solution->vehicles()[movement_.second_vehicle_id -
//   //   //  1]->route()[movement_.second_route_zone_id]->id() << std::endl;
//   //   SolutionPtr best_neighbor = std::make_shared<Solution>(*solution);
//   //   auto& first_route =
//   //       best_neighbor->vehicles()[movement_.first_vehicle_id - 1]->route();
//   //   auto& second_route =
//   //       best_neighbor->vehicles()[movement_.second_vehicle_id - 1]->route();
//   //   std::swap(first_route[movement_.first_route_zone_id],
//   //             second_route[movement_.second_route_zone_id]);
//   //   best_neighbor->UpdateRouteTime(movement_.first_vehicle_id, instance);
//   //   best_neighbor->UpdateRouteTime(movement_.second_vehicle_id, instance);
//   //   return {true, best_neighbor};
//   // }
//   // return {false, solution};
}

// bool InterSwap::IsLegalMovement(SolutionPtr solution, InterSwapTimes times,
//                                 std::shared_ptr<Instance> instance) {

// }