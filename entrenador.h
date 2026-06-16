#ifndef _ENTRENADOR_H_INCLUDED
#define _ENTRENADOR_H_INCLUDED

#include "constgym.h"

typedef struct Entrenador
{
    int id;
    char nombre[MAX_NOMBRE_TEXT];
    char genero[MAX_GENERO_TEXT];
} Entrenador;

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int size, int id, char* nombre, char* genero);
int EntrenadorBuscarEntrenadorId(Entrenador* entrenadores, int size, int id);
Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenadores, int size, int id);

Entrenador* EntrenadorObtenerEntrenador(Entrenador* entrenadores, int size, int id);
void EntrenadorObtenerEntrenadorNombre(Entrenador* entrenador, char* nombreEntrenador);
void EntrenadorObtenerEntrenadorGenero(Entrenador* entrenador, char* generoEntrenador);
void EntrenadorObtenerEntrenadoresNombresIds(Entrenador* entrenadores, int size, char nombresEntrenadores[][MAX_NOMBRE_TEXT], int* idsEntrenadores);
void EntrenadorObtenerEntrenadoresGeneros(Entrenador* entrenadores, int size, char generosEntrenadores[][MAX_GENERO_TEXT]);

void EntrenadorModificarEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombreNuevo);
void EntrenadorModificarEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* generoNuevo);

void EntrenadorOrdenarEntrenadores(Entrenador* entrenadores, int size);

#endif // _ENTRENADOR_INCLUDED
