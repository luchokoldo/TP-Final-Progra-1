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
void GymModificarSectorNombre(Gym* gym, int id);
void GymObtenerSectoresNombresIds(Gym* gym, char nombresSectores[][MAX_NOMBRE_SECTOR_SIZE], int* idsSectores);
void GymMostrarSectores(Gym* gym);
void GymEliminarSector(Gym* gym, int id);
int GymHaySectores(Gym* gym);

void GymAgregarClase(Gym* gym);
void GymModificarClaseNombre(Gym* gym, int id);
void GymEliminarClasePrecio(Gym* gym, int id);
void GymObtenerClasesNombresIds(Gym* gym, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases);
void GymMostrarClases(Gym* gym);
void GymEliminarClase(Gym* gym, int id);
int GymHayClases(Gym* gym);

void GymAsignarEntrenadorClase(Gym* gym, int idClase, int idEntrenador);
void GymEliminarEntrenadorClase(Gym* gym, int idClase);
void GymAsignarSectorClase(Gym* gym, int idClase, int idSector);
void GymEliminarSectorClase(Gym* gym, int idClase);

void GymAgregarCliente(Gym* gym);
void GymModificarClienteNombre(Gym* gym, int id);
void GymObtenerClientesNombresIds(Gym* gym, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);
void GymMostrarClientes(Gym* gym);
void GymEliminarCliente(Gym* gym, int id);
void GymAgregarClienteClase(Gym* gym, int idCliente, int idClase);
void GymEliminarClienteClase(Gym* gym, int idCliente, int idClase);
int GymHayClientes(Gym* gym);



#endif
