#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "scanner.h"
#include "utilidades.h"


static int ClienteBuscarId(Cliente* clientes, int size, int idCliente, int i);

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int idCliente, char* nombre, char* genero)
{
	Cliente nuevo = { 0 };

	nuevo.id = idCliente;

	snprintf(nuevo.nombre, MAX_NOMBRE_CLIENTE_SIZE, "%s", nombre);
	snprintf(nuevo.genero, MAX_GENERO_CLIENTE_SIZE, "%s", genero);

	nuevo.idClasesValidos = 0;

	Cliente* aux = NULL;

	aux = realloc(clientes, (size_t)(size + 1) * sizeof(Cliente));
	if (aux == NULL)
	{
		printf("[ERROR] realloc(clientes,(size_t)(size + 1) * sizeof(cliente)) devolvio NULL\n");

		return NULL;
	}

	aux[size] = nuevo;

	return aux;
}

void ClienteMostrarClientes(Cliente* clientes, int size, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases, int clasesSize)
{
	if (size <= 0)
	{
		return;
	}

	ClienteMostrarClientes(clientes, size - 1, nombresClases, idsClases, clasesSize);

	printf("\n--------------------------------------\n\n");
	printf("ID: %d\n", clientes[size - 1].id);
	printf("Nombre: %s\n", clientes[size - 1].nombre);
	printf("Genero: %s\n", clientes[size - 1].genero);
	printf("Clases: ");

	if (clientes[size - 1].idClasesValidos > 0)
	{
		for (int j = 0; j < clientes[size - 1].idClasesValidos; j++)
		{
			int idClaseActual = clientes[size - 1].idClases[j];
			int index = -1;

			for (int k = 0; k < clasesSize; k++)
			{
				if (idsClases[k] == idClaseActual)
				{
					index = k;
					break;
				}
			}

			if (index != -1)
			{
				printf("%s, ", nombresClases[index]);
			}
			else
			{
				printf("%d, ", idClaseActual);
			}
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clases asignadas.\n");
	}

	printf("\n--------------------------------------\n");
}

int ClienteBuscarClienteId(Cliente* clientes, int size, int idCliente)
{
	if (idCliente < 0)
	{
		return CLIENTE_ID_INVALIDO;
	}

	return ClienteBuscarId(clientes, size, idCliente, 0);
}

Cliente* ClienteEliminarCliente(Cliente* clientes, int size, int idCliente)
{
	int posicion = ClienteBuscarClienteId(clientes, size, idCliente);

	if (posicion == CLIENTE_ID_INVALIDO)
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
	if (cliente->idClasesValidos >= MAX_ID_CLASE_SIZE)
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

	int posicion = CLIENTE_ID_INVALIDO;

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

Cliente* ClienteObtenerCliente(Cliente* clientes, int size, int idCliente)
{
	int index = ClienteBuscarClienteId(clientes, size, idCliente);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", idCliente);

		return NULL;
	}

	return &clientes[index];
}

void ClienteObtenerClienteNombre(Cliente* cliente, char* nombreCliente)
{
	snprintf(nombreCliente, MAX_NOMBRE_CLIENTE_SIZE, "%s", cliente->nombre);
}

void ClienteObtenerClienteGenero(Cliente* cliente, char* generoCliente)
{
	snprintf(generoCliente, MAX_GENERO_CLIENTE_SIZE, "%s", cliente->genero);
}

void ClienteObtenerClientesNombresIds(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresClientes[i], MAX_NOMBRE_CLIENTE_SIZE, "%s", clientes[i].nombre);
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

int ClienteObtenerClasesEnCliente(Cliente* cliente)
{
	return cliente->idClasesValidos;
}

void ClienteModificarClienteNombre(Cliente* clientes, int size, int idCliente, char* nombreNuevo)
{
	int index = ClienteBuscarClienteId(clientes, size, idCliente);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", idCliente);

		return;
	}

	snprintf(clientes[index].nombre, MAX_NOMBRE_CLIENTE_SIZE, "%s", nombreNuevo);
}

void ClienteModificarClienteGenero(Cliente* clientes, int size, int idCliente, char* generoNuevo)
{
	int index = ClienteBuscarClienteId(clientes, size, idCliente);

	if (index == CLIENTE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d\n", idCliente);

		return;
	}

	snprintf(clientes[index].genero, MAX_GENERO_CLIENTE_SIZE, "%s", generoNuevo);
}

void ClienteMostrarCliente(Cliente* cliente, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases, int clasesSize)
{
	if (cliente == NULL)
	{
		return;
	}

	printf("\n--------------------------------------\n\n");
	printf("ID: %d\n", cliente->id);
	printf("Nombre: %s\n", cliente->nombre);
	printf("Genero: %s\n", cliente->genero);
	printf("Clases: ");

	if (cliente->idClasesValidos > 0)
	{
		for (int j = 0; j < cliente->idClasesValidos; j++)
		{
			int idClaseActual = cliente->idClases[j];
			int index = -1;

			for (int k = 0; k < clasesSize; k++)
			{
				if (idsClases[k] == idClaseActual)
				{
					index = k;

					break;
				}
			}

			if (index != -1)
			{
				printf("%s, ", nombresClases[index]);
			}
			else
			{
				printf("%d, ", idClaseActual);
			}

		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clases asignadas.\n");
	}

	printf("\n--------------------------------------\n");
}

static int ClienteBuscarId(Cliente* clientes, int size, int idCliente, int i)
{
	if (i == size)
	{
		return	

			CLIENTE_ID_INVALIDO;
	}

	if (clientes[i].id == idCliente)
	{
		return i;
	}

	i++;

	return ClienteBuscarId(clientes, size, idCliente, i);
}