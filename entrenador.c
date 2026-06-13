#include <stdio.h>
#include <stdlib.h>
#include "entrenador.h"
#include "scanner.h"
#include "utilidades.h"

static int EntrenadorBuscarId(Entrenador* entrenadores, int size, int id, int i);

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int size, int id, char* nombre, char* genero)
{
	Entrenador nuevo = { 0 };

	nuevo.id = id;

	snprintf(nuevo.nombre, MAX_NOMBRE_ENTRENADOR_SIZE, "%s", nombre);
	snprintf(nuevo.genero, MAX_GENERO_ENTRENADOR_SIZE, "%s", genero);

	Entrenador* aux = NULL;

	aux = realloc(entrenadores, (size_t)(size + 1) * sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(entrenadores, (*size + 1) * sizeof(Entrenador)) devolvio NULL");

		return NULL;
	}

	aux[size] = nuevo;

	return aux;
}

void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size)
{
	if (size <= 0)
	{
		return;
	}

	EntrenadorMostrarEntrenadores(entrenadores, size - 1);

	printf("\n--------------------------------------\n\n");
	printf("ID: %d\n", entrenadores[size - 1].id);
	printf("Nombre: %s\n", entrenadores[size - 1].nombre);
	printf("Genero: %s\n", entrenadores[size - 1].genero);
	printf("\n--------------------------------------\n");
}

int EntrenadorBuscarEntrenadorId(Entrenador* entrenadores, int size, int id)
{
	if (id < 0 || id >= size)
	{
		return ENTRENADOR_ID_INVALIDO;
	}

	return EntrenadorBuscarId(entrenadores, size, id, 0);
}

Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenadores, int size, int id)
{
	int posicion = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (posicion == ENTRENADOR_ID_INVALIDO)
	{
		printf("No se encontro el entrenador con el Id: %d\n", id);

		return entrenadores;
	}

	if (size > 1)
	{
		for (int i = posicion; i < size - 1; i++)
		{
			entrenadores[i] = entrenadores[i + 1];
		}
	}
	else
	{
		free(entrenadores);

		return NULL;
	}

	size--;

	Entrenador* aux = realloc(entrenadores, size * sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(entrenadores, size * sizeof(Entrenador)) devolvio NULL");

		return NULL;
	}

	return aux;
}

Entrenador* EntrenadorObtenerEntrenador(Entrenador* entrenadores, int size, int id)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ENTRENADOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return NULL;
	}

	return &entrenadores[index];
}

void EntrenadorObtenerEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombre)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ENTRENADOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(nombre, MAX_NOMBRE_ENTRENADOR_SIZE, "%s", entrenadores[index].nombre);
}

void EntrenadorObtenerEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* genero)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ENTRENADOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(genero, MAX_GENERO_ENTRENADOR_SIZE, "%s", entrenadores[index].genero);
}

void EntrenadorObtenerEntrenadoresNombresIds(Entrenador* entrenadores, int size, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresEntrenadores[i], MAX_NOMBRE_ENTRENADOR_SIZE, "%s", entrenadores[i].nombre);
		idsEntrenadores[i] = entrenadores[i].id;
	}
}

void EntrenadorModificarEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombreNuevo)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ENTRENADOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(entrenadores[index].nombre, MAX_NOMBRE_ENTRENADOR_SIZE, "%s", nombreNuevo);
}

void EntrenadorModificarEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* generoNuevo)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ENTRENADOR_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(entrenadores[index].genero, MAX_GENERO_ENTRENADOR_SIZE, "%s", generoNuevo);
}

static int EntrenadorBuscarId(Entrenador* entrenadores, int size, int id, int i)
{
	if (i >= size)
	{
		return ENTRENADOR_ID_INVALIDO;
	}

	if (entrenadores[i].id == id)
	{
		return i;
	}

	i++;

	return EntrenadorBuscarEntrenadorId(entrenadores, size, id, i);
}