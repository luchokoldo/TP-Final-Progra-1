#include <stdio.h>
#include <stdlib.h>
#include "clase.h"
#include "scanner.h"
#include "utilidades.h"

static int ClaseBuscarId(Clase* clase, int size, int id, int i);

Clase* ClaseAgregarClase(Clase* clases, int size, int id, char* nombre, double precio, Horario inicio, Duracion duracion)
{
	Clase nuevo = { 0 };

	nuevo.id = id;
	snprintf(nuevo.nombre, MAX_NOMBRE_CLASE_SIZE, "%s", nombre);
	nuevo.precio = precio;
	nuevo.inicio = inicio;
	nuevo.duracion=duracion ;
	nuevo.idClientesValidos = 0;
	nuevo.idEntrenador = -1; 
	nuevo.idSector = -1;

	Clase* aux = NULL;

		aux = realloc(clases, (size_t)(size + 1) * sizeof(Clase));

		if (aux == NULL)
		{
			printf("[ERROR] realloc(clases, (size_t)(size + 1) * sizeof(Clase)) devolvio NULL");

			return NULL;
		}
	
	aux[size] = nuevo;

	
	return aux;
}

void ClaseMostrarClase(Clase* clases, int size)
{
	if (size <= 0)
	{
		return;
	}

	ClaseMostrarClase(clases, size - 1);

	printf("-------------------------------------\n");
	printf("\nId de la clase: %d", clases[size-1].id);
	printf("\n Clase: %s", clases[size - 1].nombre);
	printf("\n Id entrenador: %d", clases[size - 1].idEntrenador);
	printf("\n Id sector: %d ", clases[size - 1].idSector);
	printf("\nClientes: ");

	if (clases[size - 1].idClientesValidos > 0)
	{
		for (int j = 0; j < clases[size - 1].idClientesValidos; j++)
		{
			printf("%d,", clases[size - 1].idClientes[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clientes asignados.\n");
	}
	printf("\n--------------------------------------\n");
}

int ClaseBuscarClaseId(Clase* clase, int size, int id)
{
	if (id < 0 || id >= size)
	{
		return CLASE_ID_INVALIDO;
	}

	return ClaseBuscarId(clase, size, id, 0);
}

Clase *ClaseEliminarClase(Clase* clases, int* size, int id)
{
	int posicion = ClaseBuscarClaseId(clases, *size, id);

	if (posicion == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro la clase con el id: %d\n", id);

			return clases;
	}

	if (*size > 1)
	{
		for (int i = posicion; i < (*size)-1; i++)
		{
			clases[i] = clases[i + 1];
		}
	}
	else
	{
		free(clases);

		return NULL;
	}

	(*size)--;

	Clase* aux = realloc(clases, (*size) * sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(clase, (*size) * sizeof(Clase)) devolvio NULL");

		return NULL;
	}

	return aux;
}

void ClaseAgregarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL)
	{
		return;
	}

	if (clase->idClientesValidos >= MAX_ID_CLIENTE_SIZE)
	{
		printf("[ERROR] La clase '%s' ya alcanzo el limite maximo de clientes (%d).\n",clase->nombre, MAX_ID_CLIENTE_SIZE);

		return;
	}

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			printf("[ERROR] El cliente con ID %d ya se encuentra inscrito en esta clase.\n", idCliente);

			return;
		}
	}

	clase->idClientes[clase->idClientesValidos] = idCliente;
	clase->idClientesValidos++;

	printf("Cliente %d agregado a la clase '%s'.\n", idCliente, clase->nombre);
}

void ClaseEliminarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL || clase->idClientesValidos == 0)
	{
		printf("[ERROR] La clase no contiene clientes inscriptos.\n");

		return;
	}

	int posicion = CLASE_ID_INVALIDO;

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			posicion = i;

			break;
		}
	}

	if (posicion == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro al cliente %d en la clase '%s'.\n", idCliente, clase->nombre);

		return;
	}

	for (int i = posicion; i < clase->idClientesValidos - 1; i++)
	{
		clase->idClientes[i] = clase->idClientes[i + 1];
	}

	clase->idClientesValidos--;

	printf("Cliente %d eliminado con exito de la clase '%s'.\n", idCliente, clase->nombre);
}


void ClaseAgregarEntrenador(Clase* clase, int idEntrenador)
{
	if (clase == NULL) return;

	clase->idEntrenador = idEntrenador;

	printf("Entrenador %d asignado exitosamente a la clase '%s'.\n", idEntrenador, clase->nombre);
}

void ClaseModificarEntrendor(Clase* clase, int idEntrenador)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idEntrenador = idEntrenador;

	printf("Entrenador de la clase '%s' actualizado con exito al ID: %d.\n", clase->nombre, idEntrenador);
}

void ClaseEliminarEntrenador(Clase* clase)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idEntrenador = CLASE_ID_INVALIDO;

	printf("Entrenador removido de la clase '%s' con exito.\n", clase->nombre);
}

void ClaseAgregarSector(Clase* clase, int idSector)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idSector = idSector;

	printf("Sector %d asignado exitosamente a la clase '%s'.\n", idSector, clase->nombre);
}

void ClaseModificarSector(Clase* clase, int idSector)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idSector = idSector;

	printf("Sector de la clase '%s' modificado con exito al ID: %d.\n", clase->nombre, idSector);
}

void ClaseEliminarSector(Clase* clase)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idSector = CLASE_ID_INVALIDO;

	printf("Sector removido de la clase '%s' con exito.\n", clase->nombre);
}

static int ClaseBuscarId(Clase* clase, int size, int id, int i)
{
	if (i == size)
	{
		return CLASE_ID_INVALIDO;
	}

	if (clase[i].id == id)
	{
		return i;
	}

	i++;

	return ClaseBuscarId(clase, size, id, i);
}