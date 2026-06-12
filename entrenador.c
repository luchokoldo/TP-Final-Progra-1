#include <stdio.h>
#include <stdlib.h>
#include "entrenador.h"
#include "scanner.h"
#include "utilidades.h"

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int* size, int *id)
{
	Entrenador nuevo;

	nuevo.id = *id + 1;

	printf("Ingrese nombre: ");
	ScannerString(nuevo.nombre, GET_CHARSMAX(nuevo.nombre));

	printf("Ingrese genero: ");
	ScannerString(nuevo.genero, GET_CHARSMAX(nuevo.genero));

	Entrenador* aux = NULL;

	if (entrenadores == NULL)
	{
		aux = calloc(1, sizeof(Entrenador));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Entrenador)) devolvio NULL");

			return NULL;
		}
	}
	else
	{
		aux = realloc(entrenadores, (*size + 1) * sizeof(Entrenador));

		if (aux == NULL)
		{
			printf("[ERROR] realloc(entrenadores, (*size + 1) * sizeof(Entrenador)) devolvio NULL");

			return NULL;
		}
	}

	aux[*size] = nuevo;

	(*size)++;
	(*id)++;

	return aux;
}
void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size)
{
	if (size <= 0)
	{
		return;
	}

	EntrenadorMostrarEntrenadores(entrenadores, size - 1);

	printf("\n--------------------------------------");
	printf("\nID: %d", entrenadores[size - 1].id);
	printf("\nNombre: %s", entrenadores[size - 1].nombre);
	printf("\nGenero: %s", entrenadores[size - 1].genero);
	printf("\n--------------------------------------\n");
}

int EntrenadorBuscarEntrenadorId(Entrenador* entrenador, int size, int id, int i)
{
	if (i >= size)
	{
		return -1;
	}

	if (entrenador[i].id == id)
	{
		return i;
	}

	i++;

	return EntrenadorBuscarEntrenadorId(entrenador, size, id, i);
}

void EntrenadorModificarEntrenador(Entrenador* entrenador, int size, int id)
{
	int posicion = EntrenadorBuscarEntrenadorId(entrenador, size, id, 0);

	if (posicion == -1)
	{
		printf("\nNo se encontro el entrenador con el id: %d\n", id);

		return;
	}

	printf("\n--Modificar entrenador con el Id: %d--\n", id);
	printf("\nNombre: %s", entrenador[posicion].nombre);
	printf("\nGenero: %s", entrenador[posicion].genero);
	printf("-------------------------------------------------\n");

	printf("\nIngrese el nuevo nombre: ");
	ScannerString(entrenador[posicion].nombre, GET_CHARSMAX(entrenador[posicion].nombre));

	printf("\nNombre cambiado con Exito");
}

Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenador, int* size, int id)
{
	int posicion = EntrenadorBuscarEntrenadorId(entrenador, *size, id, 0);

	if (posicion == -1)
	{
		printf("\nNo se encontro el entrenador con el Id: %d", id);

		return entrenador;
	}

	if (*size > 1)
	{
		for (int i = posicion; i < (*size)-1; i++)
		{
			entrenador[i] = entrenador[i + 1];
		}
	}
	else
	{
		free(entrenador);

		return NULL;
	}

	(*size)--;

	Entrenador* aux = realloc(entrenador, (*size) * sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(entrenador, (*size) * sizeof(Entrenador)) devolvio NULL");

		return NULL;
	}

	return aux;
}