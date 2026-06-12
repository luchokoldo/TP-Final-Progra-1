#include <stdio.h>
#include <stdlib.h>
#include "sector.h"
#include "scanner.h"
#include "utilidades.h"

Sector* SectorAgregarSector(Sector* sector, int* size, int *id)
{
	Sector nuevo;

	nuevo.id = *id + 1;

	printf("\nIngrese el nombre: ");
	ScannerString(nuevo.nombre, GET_CHARSMAX(nuevo.nombre));
	
	Sector* aux = NULL;

	if (sector == NULL)
	{
		aux = calloc(1, sizeof(Sector));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Sector)) devolvio NULL");

			return NULL;
		}
	}
	else
	{
		aux = realloc(sector, (*size + 1) * sizeof(Sector));

		if (aux == NULL)
		{
			printf("[ERROR] realloc(sector, (*size + 1) * sizeof(Sector)) devolvio NULL");

			return NULL;
		}
	}
	aux[*size] = nuevo;

	(*size)++;
	(*id)++;

	return aux;

}
void SectorMostrarSector(Sector* sectores, int size)
{

	if (size <= 0)
	{
		return;
	}
	SectorMostrarSector(sectores, size - 1);
	printf("\n--------------------------------------");
	printf("\nID: %d", sectores[size - 1].id);
	printf("\nNombre: %s", sectores[size - 1].nombre);
	printf("\n--------------------------------------\n");


}
int SectorBuscarSectorId(Sector* sectores, int size, int id, int i)
{
	if (i >= size)
	{
		return -1;
	}
	if (sectores[i].id == id)
	{
		return i;
	}

	i++;
	return SectorBuscarSectorId(sectores, size, id, i);
}
void SectorModificarSector(Sector* sector, int size, int id)
{
	int posicion = SectorBuscarSectorId(sector, size, id, 0);

	if (posicion == -1)
	{
		printf("\nNo se encontro ninguna sector con el ID: %d\n", id);
		return;
	}


	printf("\n--- Modificando sector ID: %d ---", id);
	printf("\nNombre actual: %s", sector[posicion].nombre);
	printf("---------------------------------------\n");

	printf("\nIngrese el nuevo nombre:");
	ScannerString(sector[posicion].nombre, GET_CHARSMAX(sector[posicion].nombre));
	printf("\nNombre del sector cambiado con exito!");

}
Sector *SectorEliminarSector(Sector* sector, int* size, int id)
{
	int posicion = SectorBuscarSectorId(sector, *size, id, 0);
	if (posicion == -1)
	{
		printf("No se encontro el sector con el Id: %d", id);
		return sector;
	}
	if (*size > 1)
	{
		for (int i = posicion; i < (*size)-1; i++)
		{
			sector[i] = sector[i + 1];
		}
	}
	else
	{
		free(sector);

		return NULL;
	}

	(*size)--;

	Sector* aux = realloc(sector, (*size) * sizeof(Sector));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(sector, (*size) * sizeof(Sector)) devolvio NULL");

		return NULL;
	}

	return aux;
}