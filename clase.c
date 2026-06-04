#include <stdio.h>
#include <stdlib.h>
#include "clase.h"
#include "scanner.h"
#include "utilidades.h"

Clase *ClaseAgregarClase(Clase *clases, int *size)
{
	Clase nuevo;

	printf("\nIngrese el nombre de la clase: ");
	scanString(&nuevo,GET_CHARSMAX(nuevo.nombre))
	printf("\nIngrese el id de la clase: ");
	nuevo.id = scanInt();
	printf("\nIngrese el precio de la clase:$ ");
	nuevo.precio = scanInt();
	printf("\nIngrese la hora de inicio: ");
	nuevo.inicio.horas = scanInt;
	printf("\nIingrese minutos: ");
	nuevo.inicio.minutos = scanInt();
	printf("\nIngrese la duracion de la clase en horas: ");
	nuevo.duracion.horas = scanInt();
	printf("\nIngrese la duracion en minutos");
	nuevo.duracion.minutos = scanInt();


	Clase* aux = realloc(&clases, (*size + 1), sizeof(Clase));
	if (aux == NULL)
	{
		printf("Error de memoria\n");
		return clases;
	}

	aux[*size] = nuevo;

	(*size)++;

	return aux;
}
void ClaseMostrarClase(Clase* clases, int size)
{
	if (size <= 0)
	{
		printf("Lista de clases\n");

		return;
	}

	ClaseMostrarClase(clases, size - 1);

	printf("-------------------------------------\n");
	printf("\nId de la clase: %d", clases[size-1].id);
	printf("\n Clase: %s", clases[size - 1].nombre);
	printf("\n Id entrenador: %d", clases[size - 1].idEntrenador);
	printf("\n Id sector: %d ", clases[size - 1].idSector);

	for (int j = 0; j < clases[size - 1].idClientesValidos;j++)
	{
		printf("%d,", clases[size - 1].idClientes[j]);
	}

	printf("\b\b.\n");
	printf("\n--------------------------------------\n");
}

int ClaseBuscarClaseId(Clase* clase, int size, int id,int i)
{
	if (i >= size)
	{
		return -1;
	}
	
	if (clase[i].id == id)
	{
		return i;
	}
	i++;
	return ClaseBuscarClase(clase,size,id,i);
}