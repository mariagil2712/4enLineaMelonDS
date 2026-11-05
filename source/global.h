#ifndef GLOBAL_H
#define GLOBAL_H

#define FILAS 6
#define COLUMNAS 7
#define JUGADOR1 'X'
#define JUGADOR2 'O'
#define MAX_NOMBRE 30

typedef char Tablero_t[FILAS][COLUMNAS];

// Estructura para manejar la información del jugador
typedef struct {
    char nombre[MAX_NOMBRE];
    char simbolo; // 'X' o 'O'
} Jugador_t;

#endif