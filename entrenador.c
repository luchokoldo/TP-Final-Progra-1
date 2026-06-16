#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrenador.h"
#include "scanner.h"
#include "utilidades.h"

static int EntrenadorBuscarId(Entrenador* entrenadores, int size, int id, int i);
static void EntrenadorOrdenarEntrenadorNuevo(Entrenador* entrenadores, int size);
static void EntrenadorIntercambiarEntrenadores(Entrenador* entrenadorActual, Entrenador* entrenadorAnterior);

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int size, int id, char* nombre, char* genero)
{
	Entrenador nuevo = { 0 };

	nuevo.id = id;

	snprintf(nuevo.nombre, MAX_NOMBRE_TEXT, "%s", nombre);
	snprintf(nuevo.genero, MAX_GENERO_TEXT, "%s", genero);

	Entrenador* aux = NULL;

	aux = realloc(entrenadores, (size_t)(size + 1) * sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(entrenadores, (*size + 1) * sizeof(Entrenador)) devolvio NULL");

		return NULL;
	}

	aux[size] = nuevo;

	EntrenadorOrdenarEntrenadorNuevo(aux, size);

	return aux;
}

int EntrenadorBuscarEntrenadorId(Entrenador* entrenadores, int size, int id)
{
	if (id < 0)
	{
		return ID_INVALIDO;
	}

	return EntrenadorBuscarId(entrenadores, size, id, 0);
}

Entrenador* EntrenadorEliminarEntrenador(Entrenador* entrenadores, int size, int id)
{
	int posicion = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (posicion == ID_INVALIDO)
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

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return NULL;
	}

	return &entrenadores[index];
}

void EntrenadorObtenerEntrenadorNombre(Entrenador* entrenador, char* nombreEntrenador)
{
	snprintf(nombreEntrenador, MAX_NOMBRE_TEXT, "%s", entrenador->nombre);
}

void EntrenadorObtenerEntrenadorGenero(Entrenador* entrenador, char* generoEntrenador)
{
	snprintf(generoEntrenador, MAX_GENERO_TEXT, "%s", entrenador->genero);
}

void EntrenadorObtenerEntrenadoresNombresIds(Entrenador* entrenadores, int size, char nombresEntrenadores[][MAX_NOMBRE_TEXT], int* idsEntrenadores)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresEntrenadores[i], MAX_NOMBRE_TEXT, "%s", entrenadores[i].nombre);
		idsEntrenadores[i] = entrenadores[i].id;
	}
}

void EntrenadorModificarEntrenadorNombre(Entrenador* entrenadores, int size, int id, char* nombreNuevo)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(entrenadores[index].nombre, MAX_NOMBRE_TEXT, "%s", nombreNuevo);
}

void EntrenadorModificarEntrenadorGenero(Entrenador* entrenadores, int size, int id, char* generoNuevo)
{
	int index = EntrenadorBuscarEntrenadorId(entrenadores, size, id);

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(entrenadores[index].genero, MAX_GENERO_TEXT, "%s", generoNuevo);
}

void EntrenadorOrdenarEntrenadores(Entrenador* entrenadores, int size)
{
	if (size <= 1)
	{
		return;
	}

	int indexMenor = 0;

	for (int i = 0; i < size; i++)
	{
		indexMenor = i;

		for (int j = i + 1; j < size; j++)
		{
			if (_strcmpi(entrenadores[indexMenor].nombre, entrenadores[j].nombre) > 0)
			{
				indexMenor = j;
			}
		}

		if (indexMenor != i)
		{
			EntrenadorIntercambiarEntrenadores(&entrenadores[indexMenor], &entrenadores[i]);
		}
	}
}

static int EntrenadorBuscarId(Entrenador* entrenadores, int size, int id, int i)
{
	if (i == size)
	{
		return ID_INVALIDO;
	}

	if (entrenadores[i].id == id)
	{
		return i;
	}

	i++;

	return EntrenadorBuscarId(entrenadores, size, id, i);
}

static void EntrenadorOrdenarEntrenadorNuevo(Entrenador* entrenadores, int size)
{
	if (size < 1)
	{
		return;
	}

	if (_strcmpi(entrenadores[size - 1].nombre, entrenadores[size].nombre) > 0)
	{
		EntrenadorIntercambiarEntrenadores(&entrenadores[size], &entrenadores[size - 1]);
	}

	EntrenadorOrdenarEntrenadorNuevo(entrenadores, size - 1);
}

static void EntrenadorIntercambiarEntrenadores(Entrenador* entrenadorActual, Entrenador* entrenadorAnterior)
{
	Entrenador aux = *entrenadorActual;

	*entrenadorActual = *entrenadorAnterior;
	*entrenadorAnterior = aux;
}