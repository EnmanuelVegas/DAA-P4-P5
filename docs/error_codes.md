# Códigos de error de la [máquina RAM](https://www.dim.uchile.cl/~mkiwi/written/spn/ram.pdf)

En la siguiente tabla se muestran los códigos de error para cada uno de los casos, junto con una breve descripción de los mismos.

| _Código de error_ |                                      _Significado_                                       |
| :---------------: | :--------------------------------------------------------------------------------------: |
|       **0**       |                                Acceso a etiqueta inválida                                |
|       **1**       |  Acceso a registro inexistente mediante direccionamiento directo (Ri, i >= 32 \| i < 0)  |
|       **2**       | Acceso a registro inexistente mediante direccionamiento indirecto (Ri, i >= 32 \| i < 0) |
|       **3**       |                       La instrucción no admite a R0 como operando                        |
|       **4**       |                   La instrucción no admite una constante como operando                   |
|       **5**       |                        Se ha introducido una instrucción inválida                        |
|       **6**       |                          Posición del Program Counter inválida                           |
|       **7**       |                          Archivo de instrucciones de programa no válido/encontrado       |   
|       **8**       |                          Archivo de input no válido/encontrado                           |
|       **9**       |                          ---                            |
