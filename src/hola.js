
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 * 
 * @author Diego Hernández Chico
 * @since 5 Abr 2025
 * CORREO: alu0101572062@ull.edu.es
 * Fichero con la definición de los métodos de la clase ConstructivoTransporte.
 */

 #include "../include/constructivo_transporte.h"

 /**
  * @brief Resuelve la parte de transporte del problema
  * 
  * @param solucion_parcial sobre la que construir la total
  * @return Solución completa del problema
  */
 void ConstructivoTransporte::Resolver(Resultado* solucion_parcial) {
   solucion_parcial->OrdenaTripletas();
 
   std::vector<Tripleta*> tripletas_restantes = solucion_parcial->tripletas();
   double cantidad_minima_residuos = tripletas_restantes[0]->cantidad_residuos();
   for (int i{0}; i < tripletas_restantes.size(); ++i) {
     if (cantidad_minima_residuos > tripletas_restantes[i]->cantidad_residuos()) {
       cantidad_minima_residuos = tripletas_restantes[i]->cantidad_residuos();
     }
   }
   Tripleta* tripleta_actual = nullptr;
   VehiculoTransporte* vehiculo_asignado = nullptr;
   double tiempo_total = 0;
   double tiempo_esperando = 0;
   while (!tripletas_restantes.empty()) {
     tripleta_actual = tripletas_restantes[0];
 
     tripletas_restantes.erase(tripletas_restantes.begin());
     vehiculo_asignado = SeleccionaVehiculo(solucion_parcial, tripleta_actual);
     if (vehiculo_asignado == nullptr) {
       vehiculo_asignado = new VehiculoTransporte(instancia_a_resolver_->duracion_maxima_ruta_transporte(), instancia_a_resolver_->capacidad_maxima_transporte(), instancia_a_resolver_->velocidad());
 
       vehiculo_asignado->AnadeZona(solucion_parcial, instancia_a_resolver_->vertedero(), 0);
       solucion_parcial->InsertaVehiculoTransporte(vehiculo_asignado);
     } 
     tiempo_esperando = tripleta_actual->tiempo_de_llegada() - vehiculo_asignado->duracion_actual_ruta() - TiempoParaLlegar(vehiculo_asignado, tripleta_actual->zona_transferencia()); 
     tiempo_total = TiempoParaLlegar(vehiculo_asignado, tripleta_actual->zona_transferencia());
     if (tiempo_esperando > 0){
       tiempo_total += tiempo_esperando;
     }
     vehiculo_asignado->AnadeZona(solucion_parcial, tripleta_actual->zona_transferencia(), tiempo_total, tripleta_actual->cantidad_residuos());
     if (vehiculo_asignado->ruta_asociada()->zonas_visitadas().size() == 2) {
       double instante_partida = tripleta_actual->tiempo_de_llegada() - TiempoParaLlegar(vehiculo_asignado, instancia_a_resolver_->vertedero());
       if (instante_partida >= 0) {
         vehiculo_asignado->SetInstantePartida(instante_partida);
       }
     }
     if (vehiculo_asignado->CapacidadRestante() < cantidad_minima_residuos) {
       vehiculo_asignado->AnadeZona(solucion_parcial, instancia_a_resolver_->vertedero(), 0);
     }
   }
   for (int i{0}; i < solucion_parcial->vehiculos_transporte().size(); ++i) {
     vehiculo_asignado = solucion_parcial->vehiculos_transporte()[i];
     if (vehiculo_asignado->ZonaActual() != instancia_a_resolver_->vertedero()) {
       vehiculo_asignado->AnadeZona(solucion_parcial, instancia_a_resolver_->vertedero(), TiempoParaLlegar(vehiculo_asignado, instancia_a_resolver_->vertedero()));
     }
   }
 }
 
 /**
  * @brief Selecciona el mejor vehículo para realizar una tarea
  * 
  * @param solucion_parcial con la lista de vehículos de transporte disponibles
  * @param tripleta_a_computar
  * @return mejor vehículo encontrado
  */
 VehiculoTransporte* ConstructivoTransporte::SeleccionaVehiculo(Resultado* solucion_parcial, Tripleta* tripleta_a_computar) {
   VehiculoTransporte* vehiculo_seleccionado = nullptr;
   VehiculoTransporte* vehiculo_actual = nullptr;
   double mejor_tiempo = 99999;
   double tiempo_vehiculo_actual = 0;
   double tiempo_esperando = 0;
   for (int i{0}; i < solucion_parcial->vehiculos_transporte().size(); ++i) {
     vehiculo_actual = solucion_parcial->vehiculos_transporte()[i];
     tiempo_esperando = tripleta_a_computar->tiempo_de_llegada() - vehiculo_actual->duracion_actual_ruta() - TiempoParaLlegar(vehiculo_actual, tripleta_a_computar->zona_transferencia()); 
     if (tiempo_esperando < 0) {
       tiempo_esperando = 0;
     }
     tiempo_vehiculo_actual = TiempoParaLlegar(vehiculo_actual, tripleta_a_computar->zona_transferencia());
     // Si tiene suficiente capacidad
     if (vehiculo_actual->CapacidadRestante() > 
         tripleta_a_computar->cantidad_residuos() 
         // Y tiene suficiente tiempo
         && vehiculo_actual->TiempoRestante() - TiempoEnRegresar(vehiculo_actual, tripleta_a_computar->zona_transferencia()) - tiempo_esperando > 0
         // Y le da tiempo de llegar
         && vehiculo_actual->duracion_actual_ruta() + tiempo_vehiculo_actual < tripleta_a_computar->tiempo_de_llegada()) {
       if (tiempo_vehiculo_actual < mejor_tiempo) {
         vehiculo_seleccionado = vehiculo_actual;
         mejor_tiempo = tiempo_vehiculo_actual;
       }
     }
   }
   return vehiculo_seleccionado;
 }
 
 
 /**
  * @brief Calcula el tiempo en llegar a la zona indicada, a una estación y de 
  * vuelta al depósito
  * 
  * @param vehiculo_actual que debe llegar a la zona
  * @param zona_mas_cercana encontrada que debemos comprobar
  * @return Tiempo que tarda el vehículo en realizar el recorrido
  */
 double ConstructivoTransporte::TiempoParaLlegar(VehiculoTransporte* vehiculo_actual, Zona* destino) {
   Zona* zona_actual = vehiculo_actual->ZonaActual();
   double distancia_entre_zonas = instancia_a_resolver_->distancia(zona_actual, destino);
   double horas_para_llegar = distancia_entre_zonas/vehiculo_actual->velocidad();
   return horas_para_llegar * 60;
 }
 
 /**
  * @brief Calcula el tiempo que tarda en regresar desde una nueva zona
  * 
  * @param vehiculo_actual
  * @param zona_mas_cercana
  * @param estaciones_transferencia
  */
 double ConstructivoTransporte::TiempoEnRegresar(VehiculoTransporte* vehiculo_actual, Zona* destino) {
   double tiempo_hasta_destino = TiempoParaLlegar(vehiculo_actual, destino);
   double distancia_hasta_vertedero = instancia_a_resolver_->distancia(destino, instancia_a_resolver_->vertedero());
   double tiempo_hasta_vertedero = distancia_hasta_vertedero / vehiculo_actual->velocidad() * 60;
   return tiempo_hasta_destino + tiempo_hasta_vertedero;
 }

 

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 * 
 * @author Diego Hernández Chico
 * @since 23 Mar 2025
 * CORREO: alu0101572062@ull.edu.es
 * Fichero con la declaración de la clase de los vehículos.
 */

#include <iostream>

#include "ruta.h"

class Resultado;

#ifndef VEHICULO_H
#define VEHICULO_H

class Vehiculo {
 public:
  Vehiculo(int duracion_maxima_ruta, int capacidad_maxima, int velocidad) : duracion_maxima_ruta_(duracion_maxima_ruta), capacidad_maxima_(capacidad_maxima), velocidad_(velocidad) { duracion_actual_ruta_ = 0; capacidad_actual_ = capacidad_maxima_; ruta_asociada_ = new Ruta(); }
  virtual ~Vehiculo() = 0;
  Zona* ZonaActual() { return ruta_asociada_->ZonaActual(); }
  void ImprimeRuta() { ruta_asociada_->ImprimeRuta(); }
  // Getters de la clase
  int CapacidadRestante() { return capacidad_actual_; }
  double TiempoRestante() { return duracion_maxima_ruta_ - duracion_actual_ruta_; }
  Ruta* ruta_asociada() { return ruta_asociada_; }
  double duracion_maxima_ruta() const { return duracion_maxima_ruta_; }
  double duracion_actual_ruta() const { return duracion_actual_ruta_; }
  int capacidad_maxima() const { return capacidad_maxima_; }
  int capacidad_actual() const { return capacidad_actual_; }
  int velocidad() const { return velocidad_; }
 protected:
  Ruta* ruta_asociada_;
  double duracion_maxima_ruta_;
  double duracion_actual_ruta_;
  int capacidad_maxima_;
  int capacidad_actual_;
  int velocidad_;
};

#endif

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 * 
 * @author Diego Hernández Chico
 * @since 15 Abr 2025
 * CORREO: alu0101572062@ull.edu.es
 * Fichero con la declaración de la clase de los vehículos de transporte.
 */

 #include "vehiculo.h"

 #ifndef VEHICULO_TRANSPORTE_H
 #define VEHICULO_TRANSPORTE_H
 
 class VehiculoTransporte: public Vehiculo {
  public:
   VehiculoTransporte(int duracion_maxima_ruta, int capacidad_maxima, int velocidad) : Vehiculo(duracion_maxima_ruta, capacidad_maxima, velocidad) { instante_partida_ = 0; }
   ~VehiculoTransporte() { delete ruta_asociada_; }
   void SetInstantePartida(double instante_partida) { instante_partida_ = instante_partida; }
   double instante_partida() const { return instante_partida_; }
   double TiempoRestante() { return duracion_maxima_ruta_ - duracion_actual_ruta_ + instante_partida_; }
   void AnadeZona(Resultado* solucion_actual, Zona* zona_a_anadir, double tiempo_para_llegar, double carga = 0);
  private: 
   double instante_partida_;
 };
 
 #endif
 