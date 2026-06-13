#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "scanner.h"
#include "utilidades.h"

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int id, char* nombre, char* genero)
{
	Cliente nuevo = { 0 };

	nuevo.id = id;

	snprintf(nuevo.nombre, MAX_NOMBRE_CLIENTE_SIZE, "%s", nombre);
	snprintf(nuevo.genero, MAX_GENERO_CLIENTE_SIZE, "%s", genero);

	nuevo.idClasesValidos = 0;

	Cliente* aux = NULL;

	aux = realloc(clientes, (size_t)(size + 1) * sizeof(clientes));
	if (aux == NULL)
	{
		printf("[ERROR] realloc(clientes,(size_t)(size + 1) * sizeof(cliente)) devolvio NULL");

		return NULL;
	}

	aux[size] = nuevo;

	return aux;
}

void ClienteMostrarCliente(Cliente* clientes, int size)
{
	if (size <= 0)
	{
		return;
	}

	ClienteMostrarCliente(clientes, size - 1);

	printf("\n--------------------------------------\n");
	printf("\nID: %d", clientes[size - 1].id);
	printf("\nNombre: %s", clientes[size - 1].nombre);
	printf("\nGenero: %s", clientes[size - 1].genero);
	printf("\nClases: ");

	if (clientes[size - 1].idClasesValidos > 0)
	{
		for (int j = 0; j < clientes[size - 1].idClasesValidos; j++)
		{
			printf("%d,", clientes[size - 1].idClases[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clases asignadas.\n");
	}

	printf("\n--------------------------------------\n");
}

int ClienteBuscarId(Cliente* cliente, int size, int id)
{
	if (id < 0 || id >= size)
	{
		return CLIENTE_ID_INVALIDO;
	}

	return ClienteBuscarClienteId(cliente, size, id, 0);
}

Cliente* ClienteEliminarcliente(Cliente* clientes, int size, int id)
{
	int posicion = ClienteBuscarClienteId(clientes, size, id, 0);

	if (posicion == -1)
	{
		printf("No se encontro al cliente con el Id: %d", id);

		return clientes;
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
		printf("[ERROR] realloc(cliente, (*size) * sizeof(Cliente)) devolvio NULL");

		return NULL;
	}

	return aux;
}

void ClienteAgregarClase(Cliente* cliente, int idClase)
{
	if (cliente == NULL) return;

	if (cliente->idClasesValidos >= 32)
	{
		printf("[ERROR] El cliente '%s' ya alcanzo el limite maximo de clases asignadas.\n", cliente->nombre);
		return;
	}

	for (int i = 0; i < cliente->idClasesValidos; i++)
	{
		if (cliente->idClases[i] == idClase)
		{
			printf("El cliente '%s' ya se encuentra inscripto en la clase ID %d.\n", cliente->nombre, idClase);
			return;
		}
	}

	cliente->idClases[cliente->idClasesValidos] = idClase;
	cliente->idClasesValidos++;
}

void ClienteElimarClase(Cliente* cliente, int idClase)
{
	if (cliente == NULL || cliente->idClasesValidos == 0) return;

	int posicion = -1;

	for (int i = 0; i < cliente->idClasesValidos; i++)
	{
		if (cliente->idClases[i] == idClase)
		{
			posicion = i;
			break;
		}
	}

	if (posicion == CLIENTE_ID_INVALIDO)
	{
		return;
	}

	for (int i = posicion; i < cliente->idClasesValidos - 1; i++)
	{
		cliente->idClases[i] = cliente->idClases[i + 1];
	}

	cliente->idClasesValidos--;
}



Cliente* ClienteObtenerCliente(Cliente* clientes, int size, int id)
{
	int index = ClienteBuscarClienteId(clientes, size, id, 0);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return NULL;
	}

	return &clientes[index];
}

void ClienteObtenerClienteNombre(Cliente* clientes, int size, int id, char* nombre)
{
	int index = ClienteBuscarClienteId(clientes, size, id, 0);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(nombre, MAX_NOMBRE_CLIENTE_SIZE, "%s", clientes[index].nombre);
}

void ClienteObtenerClienteGenero(Cliente* clientes, int size, int id, char* genero)
{
	int index = ClienteBuscarClienteId(clientes, size, id, 0);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(genero, MAX_GENERO_CLIENTE_SIZE, "%s", clientes[index].genero);
}

void ClienteModificarClienteNombre(Cliente* clientes, int size, int id, char* nombreNuevo)
{
	int index = ClienteBuscarClienteId(clientes, size, id, 0);

	if (index == CLIENTE_ID_INVALIDO))
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(clientes[index].nombre, MAX_NOMBRE_CLIENTE_SIZE, "%s", nombreNuevo);
}

void ClienteModificarClienteGenero(Cliente* clientes, int size, int id, char* generoNuevo)
{
	int index = ClienteBuscarClienteId(clientes, size, id, 0);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", id);

		return;
	}

	snprintf(clientes[index].genero, MAX_GENERO_CLIENTE_SIZE, "%s", generoNuevo);
}
static int ClienteBuscarId(Cliente* clientes, int size, int id, int i)
{
	if (i >= size)
	{
		return	

			CLIENTE_ID_INVALIDO;
	}

	if (clientes[i].id == id)
	{
		return i;
	}

	i++;

	return EntrenadorBuscarEntrenadorId(clientes, size, id, i);
}