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
int EntrenadorBuscarEntrenadorId(Entrenador* entrenadores, int size, int id);
Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenadores, int size, int id);

Entrenador* EntrenadorObtenerEntrenador(Entrenador* entrenadores, int size, int id);
void EntrenadorObtenerEntrenadorNombre(Entrenador* entrenador, char* nombreEntrenador);
void EntrenadorObtenerEntrenadorGenero(Entrenador* entrenador, char* generoEntrenador);
void EntrenadorObtenerEntrenadoresNombresIds(Entrenador* entrenadores, int size, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores);

void EntrenadorModificarEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombreNuevo);
void EntrenadorModificarEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* generoNuevo);

void EntrenadorOrdenarEntrenadores(Entrenador* entrenadores, int size);

#endif // _ENTRENADOR_INCLUDED
