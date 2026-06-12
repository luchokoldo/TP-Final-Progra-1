#ifndef _SECTOR_H_INCLUDED
#define _SECTOR_H_INCLUDED

#define MAX_NOMBRE_SECTOR_SIZE 64

typedef struct Sector
{
    int id;
    char nombre[MAX_NOMBRE_SECTOR_SIZE];
} Sector;

Sector* SectorAgregarSector(Sector* sector, int* size, int *id);
void SectorMostrarSector(Sector* sectores, int size);
int SectorBuscarSectorId(Sector* sectores, int size, int id, int i);
void SectorModificarSector(Sector* sector, int size, int id);
Sector* SectorEliminarSector(Sector* sectores, int* size, int id);
void SectorExportarTxt(Sector* sectores, int size);

#endif
