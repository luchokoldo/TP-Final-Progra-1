#include <stdio.h>
#include <stdlib.h>
#include "sector.h"
#include "scanner.h"
#include "utilidades.h"

Sector* SectorAgregarSector(Sector* sector, int* size)
{
	Sector nuevo;
	printf("\nIngrese el nombre del sector: ");
	ScannerString(nuevo.nombre, GET_CHARSMAX(nuevo.nombre));
	printf("Ingrese el id del sector: ");
	nuevo.id = ScannerInt();

	Sector* aux = realloc(sector, (*size) * sizeof(Sector));

	if (aux == NULL)
	{
		printf("Error de memoria\n");
		return sector;
	}

	aux[*size] = nuevo;

	(*size)++;

	return aux;

}
void SectorMostrarSector(Sector* sectores, int size)
{

	if (size <= 0)
	{
		printf("---Lista De Sectores---\n");
		return;
	}
	SectorMostrarSector(sectores, size - 1);
	printf("\n--------------------------------------");
	printf("\n ID: %d", sectores[size - 1].id);
	printf("\n Nombre: %s", sectores[size - 1].nombre);
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
	returnSectorBuscarSectorId(sectores, size, id, i);
}
void SectorModificarSector(Sector* sector, int size, int id)
{
	int posicion = SectorBuscarSectorId(sector, size, id, 0);

	if (posicion == -1)
	{
		printf("No se encontro ninguna sector con el ID: %d\n", id);
		return;
	}


	printf("\n--- Modificando sector ID: %d ---", id);
	printf("\n Nombre actual: %s", sector[posicion].nombre);
	printf("---------------------------------------\n");

	printf("\nIngrese el nuevo nombre del sector:");
	ScannerString(sector[posicion].nombre, GET_CHARSMAX(sector[posicion].nombre));
	printf("\n Nombre del sector cambiado con exito!");

}