#ifndef _SECTOR_H_INCLUDED
#define _SECTOR_H_INCLUDED

#define MAX_NOMBRE_SECTOR_SIZE 64
#define SECTOR_ID_INVALIDO      -1

typedef struct Sector
{
    int id;
    char nombre[MAX_NOMBRE_SECTOR_SIZE];
} Sector;

Sector* SectorAgregarSector(Sector* sectores, int size, int id, char* nombre);
void SectorMostrarSectores(Sector* sectores, int size);
int SectorBuscarSectorId(Sector* sectores, int size, int id);
Sector* SectorEliminarSector(Sector* sectores, int size, int id);

Sector* SectorObtenerSector(Sector* sectores, int size, int id);
void SectorObtenerSectorNombre(Sector* sectores, int size, int id, char* nombre);

void SectorModificarSectorNombre(Sector* sectores, int size, int id, char* nombreNuevo);

#endif
