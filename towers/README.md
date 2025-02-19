Towers puzzle de Simon Tatham.
Reglas:
- Todos los numeros aparecen 1 vez en cada fila y columna
- Los numeros que aparecen en los bordes dicen cuantas torres se pueden ver desde ese punto
- Puedes ver una torre si no hay otra más alta delante que la tape

Ejemplo:
   2 2 
3  1 2 3
1  3 1 2
2  2 3 1  2
   2   3

El input en tablero.txt sigue la siguiente estructura:
- Bordes en orden horario empezando por el caracter arriba a la izq
- Tablero (si es necesario). 0 representa espacio vacio. Con salto de linea para distintas filas

Un input para el ejemplo seria:
220002302213
000
010
000

O como no hay ambiguedad directamente:
220002302213
