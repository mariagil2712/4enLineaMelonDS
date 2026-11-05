/* 4 en línea
 * Código de María Antonia Gil
 * Ruta: /Users/mariaantoniagil/desktop/universidad/5tosemestre/sistemasdeprocesamiento/game
 */

//Dependencias
#include <stdio.h>
#include "logicaJuego.h"
#include "interfaz.h"
#include "global.h"

#ifdef ARM9
#include <nds.h>
#include "ndsl.h"
#endif

//Tablero
Tablero_t tablero;
//Ganador
char ganador = ' ';
//Jugadores
Jugador_t jugador1, jugador2;

//Main

int main()
{
#ifdef ARM9 //Ejecución para melon
    //Inicializar las consolas superior e inferior
    DSliteInit();

	int fichasColocadas = 0;
    int maxFichas = FILAS * COLUMNAS;
    int juegoTerminado = 0;

    inicializarTablero();

    //Pedir nombres de jugadores en la pantalla inferior
    pedirNombresJugadores(&jugador1, &jugador2);

    Jugador_t *jugadorActual = &jugador1;

    //Primer renderizado del tablero en la pantalla superior (topScreen)
    imprimirTablero();

    // Bucle principal de juego interactivo en melonDS
    while (pmMainLoop() && !juegoTerminado && fichasColocadas < maxFichas)
    {
        // 1. Mostrar turno actual en la pantalla inferior
        mostrarTurno(jugadorActual);

        // 2. Pedir columna (se queda en bucle en bottomScreen hasta recibir una valida)
        int cFicha = pedirColumna();

        // 3. Buscar la fila disponible
        int rFicha = -1;
        for (int i = FILAS - 1; i >= 0; i--)
        {
            if (tablero[i][cFicha] == ' ')
            {
                rFicha = i;
                break;
            }
        }

        if (rFicha == -1)
        {
            imprimirColumnaInvalida();
            SyncCheck();
            continue;
        }

        // 4. Colocar la ficha
        ponerFicha(tablero, rFicha, jugadorActual->simbolo, cFicha);
        fichasColocadas++;

        // 5. Redibujar el tablero actualizado en topScreen
        imprimirTablero();

        // 6. Verificar victoria
        if (verifGanador(tablero, rFicha, cFicha, jugadorActual->simbolo))
        {
            ganador = jugadorActual->simbolo;
            juegoTerminado = 1;
            mostrarGanador(jugadorActual);
        }
        else
        {
            jugadorActual = (jugadorActual == &jugador1) ? &jugador2 : &jugador1;
        }

        SyncCheck();
    }

    // Mantener la pantalla encendida y congelada con el resultado final
    while (pmMainLoop())
    {
        SyncCheck();
    }

    ExitGame();
    return 0;

#else

    int fichasColocadas = 0;
    int maxFichas = FILAS * COLUMNAS;
    char jugadorActual = JUGADOR1;
    int juegoTerminado = 0;

    inicializarTablero();
    presentarJuego();

    while (!juegoTerminado && fichasColocadas < maxFichas)
    {
        imprimirTablero();
        printf("\nTurno del Jugador: %c\n", jugadorActual);

        int cFicha;
        // detPosFicha calcula la fila y guarda la columna elegida en cFicha
        int rFicha = detPosFicha(tablero, &cFicha);

        // Colocamos la ficha en el tablero
        ponerFicha(tablero, rFicha, jugadorActual, cFicha);
        fichasColocadas = fichasColocadas + 1;

        // Verificamos si la última ficha colocada genera un 4 en línea
        if (verifGanador(tablero, rFicha, cFicha, jugadorActual))
        {
            ganador = jugadorActual;
            juegoTerminado = 1;
        }
        else
        {
            // Cambio de turno
            if (jugadorActual == JUGADOR1)
            {
                jugadorActual = JUGADOR2;
            }
            else
            {
                jugadorActual = JUGADOR1;
            }
        }
    }

    imprimirTablero();

    if (ganador != ' ')
    {
        printf("\n¡Felicidades! Ganó el jugador %c.\n", ganador);
    }
    else
    {
        printf("\n¡Empate! Se ha llenado el tablero.\n");
    }

    return 0;
#endif
}
