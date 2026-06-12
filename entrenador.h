#ifndef _ENTRENADOR_H_INCLUDED
#define _ENTRENADOR_H_INCLUDED

#define MAX_NOMBRE_ENTRENADOR_SIZE 64
#define MAX_GENERO_ENTRENADOR_SIZE 32

typedef struct Entrenador
{
    int id;
    char nombre[MAX_NOMBRE_ENTRENADOR_SIZE];
    char genero[MAX_GENERO_ENTRENADOR_SIZE];
} Entrenador;

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int* size, int *id);
void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size);
int EntrenadorBuscarEntrenadorId(Entrenador* entrenador, int size, int id, int i);
void EntrenadorModificarEntrenador(Entrenador* entrenador, int size, int id);
Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenadores, int* size, int id);
void EntrenadorExportarTxt(Entrenador* entrenadores, int size);

#endif // _ENTRENADOR_INCLUDED
