#ifndef _ENTRENADOR_H_INCLUDED
#define _ENTRENADOR_H_INCLUDED

typedef struct Entrenador
{
    int id;
    char nombre[64];
    char genero[32];
} Entrenador;
void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size);
Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int* size);
int EntrenadorBuscarEntrenadorId(Entrenador* entrenador, int size, int id, int i);
void EntrenadorModificarEntrenador(Entrenador* entrenador, int size, int id);
#endif // _ENTRENADOR_INCLUDED
