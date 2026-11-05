//Dependencias
#include "logicaJuego.h"
#include "global.h"
#include "interfaz.h"

//Funciones

int detPosFicha(Tablero_t tablero, int *cFicha)
{
    int rFicha;
    int jugadaTerminada = 0;
    while (!jugadaTerminada)
    {
        *cFicha = pedirColumna();
        //Verificación de que la columna ingresada sea válida (columna existente y NO llena)
        if ((0 <= *cFicha && *cFicha < COLUMNAS) && tablero[0][*cFicha] == ' ')
        {
            //Ubicamos la celda libre en la columna solicitada
            int i = FILAS - 1;
            while (i >= 0 && !jugadaTerminada)
            {
                if (tablero[i][*cFicha] == ' ')
                {
                    rFicha = i;
                    jugadaTerminada = 1;
                }
                else
                {
                    i = i - 1;
                }
            }
        }
        else
        {
            imprimirColumnaInvalida();
        }
    }
    return rFicha;
}

void ponerFicha(Tablero_t tablero, int rFicha, char jugador, int cFicha)
{
    tablero[rFicha][cFicha] = jugador;
}

int verifGanador(Tablero_t tablero, int rFicha, int cFicha, char jugador) {
    int hayGanador = 0; //Falso
    if (verifHorizontal(tablero, rFicha, cFicha, jugador) || verifVertical(tablero, rFicha, cFicha, jugador) || verifDiagonal(tablero, rFicha, cFicha, jugador))
    {
        hayGanador = 1;
    }
    return hayGanador;
}

//Verificar horizontal
int verifHorizontal(Tablero_t tablero, int rFicha, int cFicha, char jugador)
{
    int contador = 1; //Esto cuenta la ficha que se acaba de colocar
    int moverColumna = 1;
    int parar = 0; //False
    int ganaron = 0; //False

    //Verificar hacia la derecha
    while (!parar && !ganaron)
    {
        if (cFicha + moverColumna < COLUMNAS && tablero[rFicha][cFicha + moverColumna] == jugador)
        {
            contador = contador + 1;
            moverColumna = moverColumna + 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    moverColumna = -1;
    parar = 0;

    //Verificar hacia la izquierda
    while (!parar && !ganaron)
    {
        if (cFicha + moverColumna >= 0 && tablero[rFicha][cFicha + moverColumna] == jugador)
        {
            contador = contador + 1;
            moverColumna = moverColumna - 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    return ganaron;
}

//Verificar vertical
int verifVertical(Tablero_t tablero, int rFicha, int cFicha, char jugador)
{
    int contador = 1; //Esto cuenta la ficha que se acaba de colocar
    int moverFila = 1;
    int parar = 0; //False
    int ganaron = 0; //False

    //Verificar hacia abajo
    while (!parar && !ganaron)
    {
        if (rFicha + moverFila < FILAS && tablero[rFicha + moverFila][cFicha] == jugador)
        {
            contador = contador + 1;
            moverFila = moverFila + 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    return ganaron;
}

//Verificar diagonal
int verifDiagonal(Tablero_t tablero, int rFicha, int cFicha, char jugador)
{
    int contador = 1; //Esto cuenta la ficha que se acaba de colocar
    int mover = 1;
    int parar = 0; //False
    int ganaron = 0; //False

    // Diagonal decreciente

    //Verificar hacia arriba-izquierda
    while (!parar && !ganaron)
    {
        if (rFicha - mover >= 0 && cFicha - mover >= 0 && tablero[rFicha - mover][cFicha - mover] == jugador)
        {
            contador = contador + 1;
            mover = mover + 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    mover = 1;
    parar = 0;

    //Verificar hacia abajo-derecha
    while (!parar && !ganaron)
    {
        if (rFicha + mover < FILAS && cFicha + mover < COLUMNAS && tablero[rFicha + mover][cFicha + mover] == jugador)
        {
            contador = contador + 1;
            mover = mover + 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    //Diagonal creciente

    //Reiniciamos el contador para evaluar la otra diagonal
    contador = 1;
    mover = 1;
    parar = 0;

    //Verificar hacia abajo-izquierda
    while (!parar && !ganaron)
    {
        if (rFicha + mover < FILAS && cFicha - mover >= 0 && tablero[rFicha + mover][cFicha - mover] == jugador)
        {
            contador = contador + 1;
            mover = mover + 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    mover = 1;
    parar = 0;

    //Verificar hacia arriba-derecha
    while (!parar && !ganaron)
    {
        if (rFicha - mover >= 0 && cFicha + mover < COLUMNAS && tablero[rFicha - mover][cFicha + mover] == jugador)
        {
            contador = contador + 1;
            mover = mover + 1;
        }
        else
        {
            parar = 1;
        }
        if (contador == 4)
        {
            ganaron = 1;
        }
    }

    return ganaron;
}