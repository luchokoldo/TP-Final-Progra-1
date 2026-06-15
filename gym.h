#ifndef _GYM_H_INCLUDED
#define _GYM_H_INCLUDED

#include "entrenador.h"
#include "clase.h"
#include "sector.h"
#include "cliente.h"

#define MAX_VAR_ARRAY_SIZE	256

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

int GymAgregarEntrenador(Gym* gym, char* nombreEntrenador, char* generoEntrenador);
void GymModificarEntrenadorNombre(Gym* gym, int idEntrenador);
void GymModificarEntrenadorGenero(Gym* gym, int idEntrenador);
void GymMostrarEntrenadores(Gym* gym);
void GymMostrarEntrenador(Gym* gym, int idEntrenador);
void GymEliminarEntrenador(Gym* gym, int idEntrenador);
int GymObtenerEntrenadoresNombresIds(Gym* gym, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores);
void GymObtenerEntrenadorNombre(Gym* gym, int idEntrenador, char* nombreEntrenador);
void GymObtenerEntrenadorGenero(Gym* gym, int idEntrenador, char* generoEntrenador);
void GymExportarEntrenadoresArchivoTexto(Gym* gym);
int GymHayEntrenadores(Gym* gym);

int GymAgregarSector(Gym* gym, char* nombreSector);
void GymModificarSectorNombre(Gym* gym, int idSector);
int GymObtenerSectoresNombresIds(Gym* gym, char nombresSectores[][MAX_NOMBRE_SECTOR_SIZE], int* idsSectores);
void GymObtenerSectorNombre(Gym* gym, int idSector, char* nombreSector);
void GymMostrarSectores(Gym* gym);
void GymMostrarSector(Gym* gym, int idSector);
void GymEliminarSector(Gym* gym, int idSector);
void GymExportarSectoresArchivoTexto(Gym* gym);
int GymHaySectores(Gym* gym);

int GymAgregarClase(Gym* gym, char* nombreClase, int idEntrenador, int idSector, int horaHorario, int minutosHorario, int horaDuracion, int minutosDuracion, double precio);
void GymModificarClaseNombre(Gym* gym, int idClase, char* nombreNuevo);
void GymAsignarClasePrecio(Gym* gym, int idClase, double precioNuevo);
int GymModificarClaseHorario(Gym* gym, int idClase, int horasHorario, int minutosHorario);
int GymModificarClaseDuracion(Gym* gym, int idClase, int horasDuracion, int minutosDuracion);
int GymObtenerClasesNombresIds(Gym* gym, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases);
int GymObtenerClaseClientesNombresIds(Gym* gym, int idClase, char nombresClientes[MAX_ID_CLASE_SIZE][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);
void GymObtenerClaseNombre(Gym* gym, int idClase, char* nombreViejo);
double GymObtenerClasePrecio(Gym* gym, int idClase);
void GymObtenerClaseHorario(Gym* gym, int idClase, int* horas, int* minutos);
void GymObtenerClaseDuracion(Gym* gym, int idClase, int* horas, int* minutos);
int GymObtenerClaseEntrenadorId(Gym* gym, int idClase);
int GymObtenerClaseSectorId(Gym* gym, int idClase);
void GymEliminarClase(Gym* gym, int idClase);
void GymExportarClasesArchivoTexto(Gym* gym);
int GymHayClientesEnClase(Gym* gym, int idClase);
int GymHayEntrenadorEnClases(Gym* gym, int idEntrenador);
int GymHaySectorEnClases(Gym* gym, int idSector);
int GymHayClases(Gym* gym);

void GymAsignarEntrenadorClase(Gym* gym, int idClase, int idEntrenador);
void GymEliminarEntrenadorClase(Gym* gym, int idClase);
void GymAsignarSectorClase(Gym* gym, int idClase, int idSector);
void GymEliminarSectorClase(Gym* gym, int idClase);

int GymAgregarClienteClase(Gym* gym, int idCliente, int idClase);
void GymEliminarClienteClase(Gym* gym, int idCliente, int idClase);

int GymAgregarCliente(Gym* gym, char* nombreCliente, char* generoCliente);
void GymModificarClienteNombre(Gym* gym, int idCliente);
void GymModificarClienteGenero(Gym* gym, int idCliente);
int GymObtenerClientesNombresIds(Gym* gym, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);
int GymObtenerClienteClasesNombresIds(Gym* gym, int idCliente, char nombresClases[MAX_ID_CLIENTE_SIZE][MAX_NOMBRE_CLASE_SIZE], int* idsClases);
void GymObtenerClienteNombre(Gym* gym, int idCliente, char* nombreCliente);
void GymObtenerClienteGenero(Gym* gym, int idCliente, char* generoCliente);
void GymMostrarClientes(Gym* gym);
void GymMostrarCliente(Gym* gym, int idCliente);
void GymEliminarCliente(Gym* gym, int idCliente);
void GymExportarClientesArchivoTexto(Gym* gym);
int GymHayClasesEnCliente(Gym* gym, int idCliente);
int GymHayClientes(Gym* gym);

#endif
