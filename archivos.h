#ifndef _ARCHIVOS_H_INCLUDED
#define _ARCHIVOS_H_INCLUDED

#include "constgym.h"
#include "gym.h"

void ArchivoGuardarGym(Gym* gym);
void ArchivoCargarGym(Gym* gym);

void ArchivoAgregarEntrenador(Entrenador* entrenador);
void ArchivoAgregarSector(Sector* sector);
void ArchivoAgregarClase(Clase* clase);
void ArchivoAgregarCliente(Cliente* cliente);

void ArchivoModificarEntrenador(Entrenador* entrenador);
void ArchivoModificarSector(Sector* sector);
void ArchivoModificarClase(Clase* clase);
void ArchivoModificarCliente(Cliente* cliente);

void ArchivoBorrarEntrenador(int idEntrenador);
void ArchivoBorrarSector(int idSector);
void ArchivoBorrarClase(int idClase);
void ArchivoBorrarCliente(int idCliente);

void ArchivoExportarEntrenadores(int entrenadoresSize, int* idsEntrenadores, char nombresEntrenadores[][MAX_NOMBRE_TEXT], char generosEntrenadores[][MAX_GENERO_TEXT]);
void ArchivoExportarSectores(Sector* sectores, int size);
void ArchivoExportarClases(int clasesSize, int* idsClases, char nombresClases[][MAX_NOMBRE_TEXT], char nombresEntrenadores[][MAX_NOMBRE_TEXT],
	char nombresSectores[][MAX_NOMBRE_TEXT], int idsClasesClientes[][MAX_IDS], int clientesSize, int* idsClientes,
	char nombresClientes[][MAX_NOMBRE_TEXT], int* clasesClientesValidos, double* preciosClases, int* inicioHorasClases,
	int* inicioMinutosClases, int* duracionHorasClases, int* duracionMinutosClases);
void ArchivoExportarClientes(Cliente* clientes, int size);

void ArchivoBorrarEntrenadores(void);
void ArchivoBorrarSectores(void);
void ArchivoBorrarClases(void);
void ArchivoBorrarClientes(void);

void ArchivoActualizarIds(GymIds* ids);

#endif
