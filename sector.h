#ifndef _SECTOR_H_INCLUDED
#define _SECTOR_H_INCLUDED

typedef struct Sector
{
    int id;
    char nombre[64];
} Sector;
void SectorMostrarSector(Sector* sectores, int size);
#endif
