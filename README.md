El_juego_de_la_vida
===================

C++   Ejemplo de un autómata celular.


ENUNCIADO: El juego de la vida [1] es un ejemplo de un autómata celular, diseñado por el
matemático británico John Horton Conway en 1979. Un autómata celular es un modelo matemático
que modela a un sistema dinámico que evoluciona en pasos discretos.
El juego de la vida es un juego de cero jugadores, lo que quiere decir que su evolución está
determinada por el estado inicial y no necesita ninguna entrada de datos posterior. El tablero de
juego es una malla formada por células que se extiende por el infinito en todas las direcciones.
Cada célula tiene 8 células vecinas, que son las que están próximas a ella. Las células tienen dos
estados: “viva" o "muerta".
El estado de la malla evoluciona a lo largo de unidades de tiempo discretas (turnos). El estado de
todas las células se tiene en cuenta para calcular el estado de las mismas al turno siguiente. Todas
las células se actualizan simultáneamente.
Las transiciones dependen del número de células vecinas vivas:
• Una célula muerta con exactamente 3 células vecinas vivas "nace" (al turno siguiente
estará viva).
• Una célula viva con 2 ó 3 células vecinas vivas sigue viva, en otro caso muere o
permanece muerta (por "soledad" o "superpoblación").
