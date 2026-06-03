#ifndef _ENTRENADOR_H_INCLUDED
#define _ENTRENADOR_H_INCLUDED

typedef struct Entrenador
{
    int id;
    char nombre[64];
    char genero[32];
} Entrenador;
void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size);
#endif // _ENTRENADOR_INCLUDED
