#include <stdio.h>
#include <stdlib.h>
#include "sector.h"
#include "scanner.h"
#include "utilidades.h"

static int SectorBuscarId(Sector* sectores, int size, int id, int i);

Sector* SectorAgregarSector(Sector* sectores, int size, int id, char *nombre)
{
	Sector nuevo = { 0 };

	nuevo.id = id;

	snprintf(nuevo.nombre, MAX_NOMBRE_SECTOR_SIZE, "%s", nombre);
	
	Sector* aux = NULL;

	aux = realloc(sectores, (size_t)(size + 1) * sizeof(Sector));


		if (aux == NULL)
		{
			printf("[ERROR]  realloc(sectores, (size_t)(size + 1) * sizeof(Sector)) devolvio NULL");

			return NULL;
		}
	
	aux[size] = nuevo;

	return aux;

}
void SectorMostrarSectores(Sector* sectores, int size)
{
	if (size <= 0)
	{
		return;
	}

	SectorMostrarSectores(sectores, size - 1);

	printf("\n--------------------------------------\n\n");
	printf("ID: %d\n", sectores[size - 1].id);
	printf("Nombre: %s\n", sectores[size - 1].nombre);
	printf("\n--------------------------------------\n");
}

void SectorMostrarSector(Sector* sector)
{
	printf("\n--------------------------------------\n\n");
	printf("ID: %d\n", sector->id);
	printf("Nombre: %s\n", sector->nombre);
	printf("\n--------------------------------------\n");
}

int SectorBuscarSectorId(Sector* sectores, int size, int id)
{
	if (id < 0)
	{
		return SECTOR_ID_INVALIDO;
	}

	return SectorBuscarId(sectores, size, id, 0);
}

Sector *SectorEliminarSector(Sector* sectores, int size, int id)
{
	int posicion = SectorBuscarSectorId(sectores, size, id);

	if (posicion == SECTOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el sector con el Id: %d", id);

		return sectores;
	}
	if (size > 1)
	{
		for (int i = posicion; i < (size)-1; i++)
		{
			sectores[i] = sectores[i + 1];
		}
	}
	else
	{
		free(sectores);

		return NULL;
	}

	(size)--;

	Sector* aux = realloc(sectores, size * sizeof(Sector));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(sector, (*size) * sizeof(Sector)) devolvio NULL");

		return NULL;
	}

	return aux;
}
Sector* SectorObtenerSector(Sector* sectores, int size, int id)
{
	int index = SectorBuscarSectorId(sectores, size, id);

	if (index == SECTOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", id);

		return NULL;
	}

	return &sectores[index];
}

void SectorObtenerSectorNombre(Sector* sectores, int size, int id, char* nombre)
{
	int index = SectorBuscarSectorId(sectores, size, id);

	if (index == SECTOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", id);

		return;
	}

	snprintf(nombre, MAX_NOMBRE_SECTOR_SIZE, "%s", sectores[index].nombre);
}

void SectorObtenerSectoresNombresIds(Sector* sectores, int size, char nombresSectores[][MAX_NOMBRE_SECTOR_SIZE], int* idsSectores)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresSectores[i], MAX_NOMBRE_SECTOR_SIZE, "%s", sectores[i].nombre);
		idsSectores[i] = sectores[i].id;
	}
}

void SectorModificarSectorNombre(Sector* sectores, int size, int id, char* nombreNuevo)
{
	int index = SectorBuscarSectorId(sectores, size, id);

	if (index == SECTOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", id);

		return;
	}

	snprintf(sectores[index].nombre, MAX_NOMBRE_SECTOR_SIZE, "%s", nombreNuevo);
}

static int SectorBuscarId(Sector* sectores, int size, int id, int i)
{
	if (i == size)
	{
		return SECTOR_ID_INVALIDO;
	}

	if (sectores[i].id == id)
	{
		return i;
	}

	i++;

	return SectorBuscarId(sectores, size, id, i);
}