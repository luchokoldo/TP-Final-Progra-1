#ifndef _SECTOR_H_INCLUDED
#define _SECTOR_H_INCLUDED

typedef struct Sector
{
    int id;
    char nombre[64];
} Sector;
void SectorMostrarSector(Sector* sectores, int size);
Sector* SectorAgregarSector(Sector* sector, int* size);
int SectorBuscarSectorId(Sector* sectores, int size, int id, int i);
void SectorModificarSector(Sector* sector, int size, int id);
#endif
