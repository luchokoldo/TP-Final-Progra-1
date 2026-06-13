#ifndef _GYM_H_INCLUDED
#define _GYM_H_INCLUDED

#include "entrenador.h"
#include "clase.h"
#include "sector.h"
#include "cliente.h"

typedef struct GymIds
{
	int entrenador;
	int clase;
	int sector;
	int cliente;
} GymIds;

typedef struct Gym
{
	Entrenador* entrenadores;
	int entrenadoresSize;
	Clase* clases;
	int clasesSize;
	Sector* sectores;
	int sectoresSize;
	Cliente* clientes;
	int clientesSize;
	GymIds ids;
} Gym;

void GymAgregarEntrenador(Gym* gym);
void GymModificarEntrenadorNombre(Gym* gym, int id);
void GymModificarEntrenadorGenero(Gym* gym, int id);
void GymMostrarEntrenadores(Gym* gym);
void GymEliminarEntrenador(Gym* gym, int id);
void GymObtenerEntrenadoresNombresIds(Gym* gym, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores);
int GymHayEntrenadores(Gym* gym);

void GymAgregarSector(Gym* gym);

void GymAgregarClase(Gym* gym);

void GymAgregarCliente(Gym* gym);


#endif
