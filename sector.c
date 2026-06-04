#include <stdio.h>
#include "sector.h"

void SectorMostrarSector(Sector* sectores, int size)
{
	printf("---Lista De Sectores---\n");
	for (int i = 0; i < size; i++)
	{
		printf("\n--------------------------------------");
		printf("\n ID: %d", sectores[i].id);
		printf("\n Nombre: %s", sectores[i].nombre);
		printf("\n--------------------------------------\n");
	}


}