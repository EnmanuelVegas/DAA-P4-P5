# DAA-P4-2024-2025

## P6: Enmanuel Vegas Acosta (alu0101281698@ull.edu.es)

Uso: `./max_diversity FILE|DIRECTORY -g <LRC> [-l] [-bb]`

Programa para resolver el Problema de Máxima Diversidad (MDP) para el fichero 
FILE o para todos los ficheros especificados en la ruta DIRECTORY.

Se pueden emplear 4 algoritmos: Constructivo voraz, GRASP, Búsqueda Local y Ramificación
y poda.

## Parámetros obligatorios:
- `FILE | DIRECTORY`:       Ruta al fichero o directorio que contiene los datos 
                            del problema.
- `-g, --grasp <LRC>`:      Tamaño de la lista restringida de candidatos (LRC).

## Parámetros opcionales:
-  `-l, --localsearch`      Aplica el algoritmo de búsqueda local a la salida del
                            voraz o GRASP.
-  `-bb, --branchbound`     Aplica el algoritmo de ramificación y poda a la salida
                            del voraz o GRASP.


### Nota
Si no se emplea ningún parámetro opcional, entonces se aplicará, por defecto,
el algoritmo voraz o GRASP (dependiendo del tamaño de LRC).
IMPORTANTE: Para ejecutar el voraz constructivo se ejecuta el programa con tamaño
de LRC = 1

