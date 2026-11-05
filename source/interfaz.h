#ifndef INTERFAZ_H
#define INTERFAZ_H

//Dependencias
#include "global.h"

//Funciones

extern Tablero_t tablero;

//Llenar el tablero inicialmente vacío
void inicializarTablero();

//Imprimir el tablero como esté actualmente
void imprimirTablero();

//Lee desde consola la columna de la jugada
int pedirColumna();

//Imprime mensaje de error si la columna deseada es inválida
void imprimirColumnaInvalida();

//Imprime presentación inicial del juego
void presentarJuego();

//Función para registrar nombres de ambos jugadores
void pedirNombresJugadores(Jugador_t *j1, Jugador_t *j2);

//Para imprimir durante el main en qué turno estamos
void mostrarTurno(const Jugador_t *jugador);

//Para mostrar al final del juego (si es que hubo) ganador
void mostrarGanador(const Jugador_t *jugador);



#endif