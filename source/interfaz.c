//Dependencias
#include "interfaz.h"
#include "global.h"
#include <stdio.h>

#ifdef ARM9
#include <nds.h>
#include "ndsl.h"
#endif

//Funciones
void inicializarTablero()
{
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = ' ';
        }
    }
}

void presentarJuego()
{
    printf("¡Bienvenido a 4 en línea! \n Logra agrupar 4 fichas horizontal vertical o diagonalmente y gánale a tu oponente. \n Presentado por María Antonia Gil\n\n");
}

void pedirNombresJugadores(Jugador_t *j1, Jugador_t *j2)
{
    j1->simbolo = JUGADOR1;
    j2->simbolo = JUGADOR2;

#ifdef ARM9
    char line[100];

    consoleSelect(&bottomScreen);
    consoleClear();
    printf("--- REGISTRO DE JUGADORES ---\n\n");

    printf("Nombre Jugador 1 (%c): ", JUGADOR1);
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%29s", j1->nombre);
    if (strlen(j1->nombre) == 0) strcpy(j1->nombre, "Jugador_1");

    printf("\nNombre Jugador 2 (%c): ", JUGADOR2);
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%29s", j2->nombre);
    if (strlen(j2->nombre) == 0) strcpy(j2->nombre, "Jugador_2");
#else
    printf("--- REGISTRO DE JUGADORES ---\n");
    printf("Ingrese el nombre del Jugador 1 (%c): ", JUGADOR1);
    scanf("%29s", j1->nombre);

    printf("Ingrese el nombre del Jugador 2 (%c): ", JUGADOR2);
    scanf("%29s", j2->nombre);
#endif
}

void imprimirTablero(void)
{
#ifdef ARM9
    // Dirigir la salida explícitamente a la pantalla superior y limpiarla
    consoleSelect(&topScreen);
    consoleClear();
#endif

    printf("\n==== TABLERO 4 EN LINEA ====\n\n");
    for (int i = 0; i < FILAS; i++) {
        printf("|");
        for (int j = 0; j < COLUMNAS; j++) {
            printf(" %c |", tablero[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------\n");
    printf(" 0   1   2   3   4   5   6\n");
}

void mostrarTurno(const Jugador_t *jugador)
{
#ifdef ARM9
    // Dirigir la salida explícitamente a la pantalla inferior y limpiarla
    consoleSelect(&bottomScreen);
    consoleClear();
    printf("Turno de %s (%c)\n\n", jugador->nombre, jugador->simbolo);
#else
    printf("\nTurno de %s (%c)\n", jugador->nombre, jugador->simbolo);
#endif
}

int pedirColumna()
{
    int cFicha = -1;

#ifdef ARM9
    char entrada[3]; // Espacio justo para 1 carácter + '\n' + '\0'
    int valido = 0;

    while (!valido)
    {
		consoleSelect(&bottomScreen);
        printf("Ingrese la columna donde desee poner su ficha:\n");

        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            // Si el usuario escribió más de un carácter, limpiamos el resto del búfer stdin
            if (strchr(entrada, '\n') == NULL)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }

            // Validamos que el único carácter ingresado sea un dígito entre '0' y '6'
            if (entrada[0] >= '0' && entrada[0] <= '6')
            {
                cFicha = entrada[0] - '0'; // Convierte el carácter numérico a entero
                valido = 1;
            }
            else if (entrada[0] < '0' || entrada[0] > '9')
            {
                printf("Ingresaste un caracter no numerico.\n");
            }
            else
            {
                imprimirColumnaInvalida();
            }
        }
    }
#else
    int validez;
    while (cFicha == -1)
    {
        printf("Ingrese la columna donde desee poner su ficha: \n");
        validez = scanf("%d", &cFicha);
        if (validez != 1)
        {
            printf("Ingresaste un caracter no numérico. \n");
            while (getchar() != '\n');
        }
    }
#endif

    return cFicha;
}

void imprimirColumnaInvalida()
{
    printf("La columna ingresada es invalida \n");
}

void mostrarGanador(const Jugador_t *jugador)
{
#ifdef ARM9
    consoleSelect(&bottomScreen);
    consoleClear();
    printf(" ¡Felicidades! El ganador es %s (%c).\n", jugador->nombre, jugador->simbolo);
    printf("Presione START para salir.\n");
#else
    printf("\n¡Felicidades! El ganador es %s (%c).\n", jugador->nombre, jugador->simbolo);
#endif
}