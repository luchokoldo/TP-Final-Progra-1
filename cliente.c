#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "scanner.h"
#include "utilidades.h"

Cliente* ClienteAgregarCliente(Cliente* clientes, int* size)
{
	Cliente nuevo;
	printf("\nIngrese el Id del cliente: ");
	nuevo.id = scanInt();
	printf("\nIngrese el nombre del cliente : ");
	scanString(&nuevo.nombre, GET_CHARSMAX(nuevo.nombre));
	printf("\nIngrese el genero del cliente:");
	scanString(nuevo.genero, GET_CHARSMAX(nuevo.genero));
	Cliente* aux = realloc(clientes, (*size + 1) * sizeof(Cliente));

	if (aux == NULL)
	{
		printf("Error de memoria\n");
		return clientes;
	}

	aux[*size] = nuevo;

	(*size)++;

	return aux;

}
void ClienteMostrarCliente(Cliente* clientes, int size)
{
	if (size <= 0)
	{
		printf("\tLista de clientes");
		return;
	}
	ClienteMostrarCliente(clientes, size - 1);

	printf("\n--------------------------------------\n");
	printf("\nID: %d", clientes[size - 1].id);
	printf("\nNombre: %s", clientes[size - 1].nombre);
	printf("\nGenero: %s", clientes[size - 2].genero);
	printf("\nClases: ");
	for (int z = 0; z < clientes[size - 1].idClasesValidos; z++)
	{
		printf("%d, ", clientes[size - 1].idClases[z]);

	}
	printf("\b\b.\n");
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

	return ClienteBuscarCliente(cliente, size, id, i);
}