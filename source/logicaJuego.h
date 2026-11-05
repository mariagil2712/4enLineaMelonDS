//Dependencias
#include "global.h"

//Funciones

//Detección de posición de ficha
int detPosFicha(Tablero_t tablero, int *cFicha);

//Efecto de la jugada
void ponerFicha(Tablero_t tablero, int rFicha, char jugador, int columna);

//Verificar ganador
int verifGanador(Tablero_t tablero, int rFicha, int cFicha, char jugador);

//Verificar horizontal
int verifHorizontal(Tablero_t tablero, int rFicha, int cFicha, char jugador);

//Verificar vertical
int verifVertical(Tablero_t tablero, int rFicha, int cFicha, char jugador);

//Verificar diagonal
int verifDiagonal(Tablero_t tablero, int rFicha, int cFicha, char jugador);