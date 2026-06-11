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

#endif
