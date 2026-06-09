#ifndef _ARCHIVOS_INCLUDED
#define _ARCHIVOS_INCLUDED

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

void ArchivoBorrarEntrenador(Entrenador* entrenador);
void ArchivoBorrarSector(Sector* sector);
void ArchivoBorrarClase(Clase* clase);
void ArchivoBorrarCliente(Cliente* cliente);

void ArchivoExportarEntrenadores(Entrenador* entrenadores, int size);
void ArchivoExportarSectores(Sector* sectores, int size);
void ArchivoExportarClases(Clase* clases, int size);
void ArchivoExportarClientes(Cliente* clientes, int size);

#endif
