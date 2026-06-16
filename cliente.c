#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "scanner.h"
#include "utilidades.h"


static int ClienteBuscarId(Cliente* clientes, int size, int idCliente, int i);
static void ClienteOrdenarClienteNuevo(Cliente* cliente, int size);
static void ClienteIntercambiarClientes(Cliente* clienteActual, Cliente* clienteAnterior);

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int idCliente, char* nombre, char* genero)
{
	Cliente nuevo = { 0 };

	nuevo.id = idCliente;

	snprintf(nuevo.nombre, MAX_NOMBRE_TEXT, "%s", nombre);
	snprintf(nuevo.genero, MAX_GENERO_TEXT, "%s", genero);

	nuevo.idClasesValidos = 0;

	Cliente* aux = NULL;

	aux = realloc(clientes, (size_t)(size + 1) * sizeof(Cliente));
	if (aux == NULL)
	{
		printf("[ERROR] realloc(clientes,(size_t)(size + 1) * sizeof(cliente)) devolvio NULL\n");

		return NULL;
	}

	aux[size] = nuevo;

	ClienteOrdenarClienteNuevo(aux, size);

	return aux;
}

int ClienteBuscarClienteId(Cliente* clientes, int size, int idCliente)
{
	if (idCliente < 0)
	{
		return ID_INVALIDO;
	}

	return ClienteBuscarId(clientes, size, idCliente, 0);
}

Cliente* ClienteEliminarCliente(Cliente* clientes, int size, int idCliente)
{
	int posicion = ClienteBuscarClienteId(clientes, size, idCliente);

	if (posicion == ID_INVALIDO)
	{
		printf("No se encontro al cliente con el Id: %d\n", idCliente);

		return NULL;
	}

	if (size > 1)
	{
		for (int i = posicion; i < (size)-1; i++)
		{
			clientes[i] = clientes[i + 1];
		}
	}
	else
	{
		free(clientes);

		return NULL;
	}

	(size)--;

	Cliente* aux = realloc(clientes, size * sizeof(Cliente));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(cliente, (*size) * sizeof(Cliente)) devolvio NULL\n");

		return NULL;
	}

	return aux;
}

int ClienteAgregarClase(Cliente* cliente, int idClase)
{
	if (cliente->idClasesValidos >= MAX_IDS)
	{
		printf("[ERROR] El cliente '%s' ya alcanzo el limite maximo de clases asignadas\n", cliente->nombre);

		return 0;
	}

	for (int i = 0; i < cliente->idClasesValidos; i++)
	{
		if (cliente->idClases[i] == idClase)
		{
			printf("[ERROR] El cliente '%s' ya se encuentra inscripto en la clase\n", cliente->nombre);

			return 0;
		}
	}

	cliente->idClases[cliente->idClasesValidos] = idClase;
	cliente->idClasesValidos++;

	return 1;
}

void ClienteEliminarClase(Cliente* cliente, int idClase)
{
	if (cliente == NULL || cliente->idClasesValidos == 0) return;

	int posicion = ID_INVALIDO;

	for (int i = 0; i < cliente->idClasesValidos; i++)
	{
		if (cliente->idClases[i] == idClase)
		{
			posicion = i;

			break;
		}
	}

	if (posicion == ID_INVALIDO)
	{
		return;
	}

	for (int i = posicion; i < cliente->idClasesValidos - 1; i++)
	{
		cliente->idClases[i] = cliente->idClases[i + 1];
	}

	cliente->idClasesValidos--;
}

Cliente* ClienteObtenerCliente(Cliente* clientes, int size, int idCliente)
{
	int index = ClienteBuscarClienteId(clientes, size, idCliente);

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", idCliente);

		return NULL;
	}

	return &clientes[index];
}

void ClienteObtenerClienteNombre(Cliente* cliente, char* nombreCliente)
{
	snprintf(nombreCliente, MAX_NOMBRE_TEXT, "%s", cliente->nombre);
}

void ClienteObtenerClienteGenero(Cliente* cliente, char* generoCliente)
{
	snprintf(generoCliente, MAX_GENERO_TEXT, "%s", cliente->genero);
}

void ClienteObtenerClientesNombresIds(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_TEXT], int* idsClientes)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresClientes[i], MAX_NOMBRE_TEXT, "%s", clientes[i].nombre);
		idsClientes[i] = clientes[i].id;
	}
}

void ClienteObtenerClienteClasesIds(Cliente* cliente, int* idsClases)
{
	for (int i = 0; i < cliente->idClasesValidos; i++)
	{
		idsClases[i] = cliente->idClases[i];
	}
}

int ClienteObtenerCantidadClasesEnCliente(Cliente* cliente)
{
	return cliente->idClasesValidos;
}

void ClienteModificarClienteNombre(Cliente* clientes, int size, int idCliente, char* nombreNuevo)
{
	int index = ClienteBuscarClienteId(clientes, size, idCliente);

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", idCliente);

		return;
	}

	snprintf(clientes[index].nombre, MAX_NOMBRE_TEXT, "%s", nombreNuevo);
}

void ClienteModificarClienteGenero(Cliente* clientes, int size, int idCliente, char* generoNuevo)
{
	int index = ClienteBuscarClienteId(clientes, size, idCliente);

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", idCliente);

		return;
	}

	snprintf(clientes[index].genero, MAX_GENERO_TEXT, "%s", generoNuevo);
}

void ClienteOrdenarClientes(Cliente* cliente, int size)
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
			if (_strcmpi(cliente[indexMenor].nombre, cliente[j].nombre) > 0)
			{
				indexMenor = j;
			}
		}

		if (indexMenor != i)
		{
			ClienteIntercambiarClientes(&cliente[indexMenor], &cliente[i]);
		}
	}
}

static int ClienteBuscarId(Cliente* clientes, int size, int idCliente, int i)
{
	if (i == size)
	{
		return	

			ID_INVALIDO;
	}

	if (clientes[i].id == idCliente)
	{
		return i;
	}

	i++;

	return ClienteBuscarId(clientes, size, idCliente, i);
}

static void ClienteOrdenarClienteNuevo(Cliente* clientes, int size)
{
	if (size < 1)
	{
		return;
	}

	if (_strcmpi(clientes[size - 1].nombre, clientes[size].nombre) > 0)
	{
		ClienteIntercambiarClientes(&clientes[size], &clientes[size - 1]);
	}

	ClienteOrdenarClienteNuevo(clientes, size - 1);
}

static void ClienteIntercambiarClientes(Cliente* clienteActual, Cliente* clienteAnterior)
{
	Cliente aux = *clienteActual;

	*clienteActual = *clienteAnterior;
	*clienteAnterior = aux;
}