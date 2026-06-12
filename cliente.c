#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "scanner.h"
#include "utilidades.h"

Cliente* ClienteAgregarCliente(Cliente* clientes, int* size, int *id)
{
	Cliente nuevo;

	nuevo.id = *id + 1;

	printf("Ingrese el nombre: ");
	ScannerString(nuevo.nombre, GET_CHARSMAX(nuevo.nombre));

	printf("Ingrese el genero: ");
	ScannerString(nuevo.genero, GET_CHARSMAX(nuevo.genero));

	Cliente* aux = NULL;

	if (clientes == NULL)
	{
		aux = calloc(1, sizeof(Cliente));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(clientes)) devolvio NULL");

			return NULL;
		}
	}
	else
	{
		aux = realloc(clientes, (*size + 1) * sizeof(Cliente));

		if (aux == NULL)
		{
			printf("[ERROR] realloc(clientes, (*size + 1) * sizeof(Cliente)) devolvio NULL");

			return NULL;
		}
	}
	aux[*size] = nuevo;

	(*size)++;
	(*id)++;

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

int ClienteBuscarClienteId(Cliente* cliente, int size, int id, int i)
{
	if (i >= size)
	{
		return -1;
	}

	if (cliente[i].id == id)
	{
		return i;
	}

	i++;

	return ClienteBuscarClienteId(cliente, size, id, i);
}

void ClienteModificarCliente(Cliente* cliente, int size, int id)
{
	int posicion = ClienteBuscarClienteId(cliente, size, id, 0);

		if (posicion == -1)
		{
			printf("\nno se encontro el cliente con el id: %d\n", id);

				return;
		}

		printf("--Modificar cliente Id: %d--\n", id);
		printf("\nNombre: %s", cliente[posicion].nombre);
		printf("\nGenero: %s", cliente[posicion].genero);
		printf("\nClases validas: %d", cliente[posicion].idClasesValidos);
		printf("-------------------------------------------------\n");
		
		
		printf("Ingrese el nuevo nombre: ");
		ScannerString(cliente[posicion].nombre, GET_CHARSMAX(cliente[posicion].nombre));

		printf("Ingrese el nuevo genero : ");
		ScannerString(cliente[posicion].genero, GET_CHARSMAX(cliente[posicion].genero));

		printf("\nCliente modificado con exito");
}

Cliente *ClienteEliminarcliente(Cliente* cliente, int* size, int id)
{
	int posicion = ClienteBuscarClienteId(cliente,*size,id, 0);

	if (posicion == -1)
	{
		printf("No se encontro al cliente con el Id: %d", id);

		return cliente;
	}
	if (*size > 1)
	{
		for (int i = posicion; i < (*size)-1 ; i++)
		{
			cliente[i] = cliente[i + 1];
		}
	}
	else
	{
		free(cliente);

		return NULL;
	}

	(*size)--;

	Cliente* aux = realloc(cliente, (*size) * sizeof(Cliente));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(cliente, (*size) * sizeof(Cliente)) devolvio NULL");

		return NULL;
	}

	return aux;
}
void ClienteAgregarClase(Cliente* cliente, int idClase)
{

}
void ClienteElimarClase(Cliente* cliente, int idClase)
{

}