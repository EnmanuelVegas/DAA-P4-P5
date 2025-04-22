# DAA-P4-2024-2025


Uso: ./vrpt_routes [FILE | DIRECTORY] -g <LRC> -m <REPS>

Programa para resolver el problema VRPT-STWS para el fichero FILE o para todos
los ficheros especificados en la ruta DIRECTORY.

Parámetros obligatorios:
  -g, --grasp [LRC]        Tamaño de la lista restringida de candidatos (LRC)
  -m, --multi [REPS]       Número de repeticiones para el MultiStart.

IMPORTANTE: Para ejecutar el Greedy constructivo se ejecuta el programa con tamaño
de LRC = 1

