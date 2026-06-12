#ifndef _ENTRENADOR_H_INCLUDED
#define _ENTRENADOR_H_INCLUDED

#define MAX_NOMBRE_ENTRENADOR_SIZE  64
#define MAX_GENERO_ENTRENADOR_SIZE  32

#define ENTRENADOR_ID_INVALIDO      -1

typedef struct Entrenador
{
    int id;
    char nombre[MAX_NOMBRE_ENTRENADOR_SIZE];
    char genero[MAX_GENERO_ENTRENADOR_SIZE];
} Entrenador;

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int size, int id, char* nombre, char* genero);
void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size);
int EntrenadorBuscarEntrenadorId(Entrenador* entrenadores, int size, int id, int i);
Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenadores, int size, int id);

Entrenador* EntrenadorObtenerEntrenador(Entrenador* entrenadores, int size, int id);
void EntrenadorObtenerEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombre);
void EntrenadorObtenerEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* genero);
void EntrenadorObtenerEntrenadoresNombresIds(Entrenador* entrenadores, int size, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores);

void EntrenadorModificarEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombreNuevo);
void EntrenadorModificarEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* generoNuevo);

#endif // _ENTRENADOR_INCLUDED
