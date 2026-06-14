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
void GymModificarEntrenadorNombre(Gym* gym, int idEntrenador);
void GymModificarEntrenadorGenero(Gym* gym, int idEntrenador);
void GymMostrarEntrenadores(Gym* gym);
void GymMostrarEntrenador(Gym* gym, int idEntrenador);
void GymEliminarEntrenador(Gym* gym, int idEntrenador);
int GymObtenerEntrenadoresNombresIds(Gym* gym, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores);
void GymExportarEntrenadoresArchivoTexto(Gym* gym);
int GymHayEntrenadores(Gym* gym);

void GymAgregarSector(Gym* gym);
void GymModificarSectorNombre(Gym* gym, int idSector);
int GymObtenerSectoresNombresIds(Gym* gym, char nombresSectores[][MAX_NOMBRE_SECTOR_SIZE], int* idsSectores);
void GymMostrarSectores(Gym* gym);
void GymMostrarSector(Gym* gym, int idSector);
void GymEliminarSector(Gym* gym, int idSector);
void GymExportarSectoresArchivoTexto(Gym* gym);
int GymHaySectores(Gym* gym);

void GymAgregarClase(Gym* gym);
void GymModificarClaseNombre(Gym* gym, int idClase);
void GymAsignarClasePrecio(Gym* gym, int idClase);
void GymModificarClaseHorario(Gym* gym, int idClase);
void GymModificarClaseDuracion(Gym* gym, int idClase);
int GymObtenerClasesNombresIds(Gym* gym, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases);
int GymObtenerClaseClientesNombresIds(Gym* gym, int idClase, char nombresClientes[MAX_ID_CLASE_SIZE][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);
void GymMostrarClases(Gym* gym);
void GymMostrarClase(Gym* gym, int idClase);
void GymEliminarClase(Gym* gym, int idClase);
void GymExportarClasesArchivoTexto(Gym* gym);
int GymHayClientesEnClase(Gym* gym, int idClase);
int GymHayClases(Gym* gym);

void GymAsignarEntrenadorClase(Gym* gym, int idClase, int idEntrenador);
void GymEliminarEntrenadorClase(Gym* gym, int idClase);
void GymAsignarSectorClase(Gym* gym, int idClase, int idSector);
void GymEliminarSectorClase(Gym* gym, int idClase);

void GymAgregarClienteClase(Gym* gym, int idCliente, int idClase);
void GymEliminarClienteClase(Gym* gym, int idCliente, int idClase);

void GymAgregarCliente(Gym* gym);
void GymModificarClienteNombre(Gym* gym, int idCliente);
void GymModificarClienteGenero(Gym* gym, int idCliente);
int GymObtenerClientesNombresIds(Gym* gym, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);
int GymObtenerClienteClasesNombresIds(Gym* gym, int idCliente, char nombresClases[MAX_ID_CLIENTE_SIZE][MAX_NOMBRE_CLASE_SIZE], int* idsClases);
void GymMostrarClientes(Gym* gym);
void GymMostrarCliente(Gym* gym, int idCliente);
void GymEliminarCliente(Gym* gym, int idCliente);
void GymExportarClientesArchivoTexto(Gym* gym);
int GymHayClasesEnCliente(Gym* gym, int idCliente);
int GymHayClientes(Gym* gym);

#endif
