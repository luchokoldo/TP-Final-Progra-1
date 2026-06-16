#ifndef _SECTOR_H_INCLUDED
#define _SECTOR_H_INCLUDED

#include "constgym.h"

typedef struct Sector
{
    int id;
    char nombre[MAX_NOMBRE_TEXT];
} Sector;

Sector* SectorAgregarSector(Sector* sectores, int size, int id, char* nombre);
int SectorBuscarSectorId(Sector* sectores, int size, int id);
Sector* SectorEliminarSector(Sector* sectores, int size, int id);

Sector* SectorObtenerSector(Sector* sectores, int size, int id);
void SectorObtenerSectorNombre(Sector* sector, char* nombreSector);
void SectorObtenerSectoresNombresIds(Sector* sectores, int size, char nombresSectores[][MAX_NOMBRE_TEXT], int* idsSectores);

void SectorModificarSectorNombre(Sector* sectores, int size, int id, char* nombreNuevo);

void SectorOrdenarSectores(Sector* sectores, int size);

#endif
