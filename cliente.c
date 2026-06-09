#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "scanner.h"
#include "utilidades.h"

Cliente* ClienteAgregarCliente(Cliente* clientes, int* size)
{
	Cliente nuevo;
	printf("\nIngrese el Id del cliente: ");
	nuevo.id = ScannerInt();
	printf("\nIngrese el nombre del cliente : ");
	ScannerString(nuevo.nombre, GET_CHARSMAX(nuevo.nombre));
	printf("\nIngrese el genero del cliente:");
	ScannerString(nuevo.genero, GET_CHARSMAX(nuevo.genero));
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
		return;
	}
	ClienteMostrarCliente(clientes, size - 1);

	printf("\n--------------------------------------\n");
	printf("\nID: %d", clientes[size - 1].id);
	printf("\nNombre: %s", clientes[size - 1].nombre);
	printf("\nGenero: %s", clientes[size - 1].genero);
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
		printf("\nNombre del cliente: %s", cliente[posicion].nombre);
		printf("\nGenero: %s", cliente[posicion].genero);
		printf("\nClases validas: %d", cliente[posicion].idClasesValidos);
		printf("-------------------------------------------------\n");
		
		
		printf(" Ingrese el nuevo nombre del cliente: ");
		ScannerString(cliente[posicion].nombre, GET_CHARSMAX(cliente[posicion].nombre));

		printf(" Ingrese el nuevo genero del cliente: ");
		ScannerString(cliente[posicion].genero, GET_CHARSMAX(cliente[posicion].genero));
		printf("\n Cliente modificado con exito");
}
Cliente *ClienteEliminarcliente(Cliente* cliente, int* size, int id)
{
	int posicion = ClienteBuscarClienteId(cliente,size,id, 0);
	if (posicion == -1)
	{
		printf("No se encontro al cliente con el Id: %d", id);
		return cliente;
	}
	for (int i = posicion; i < (*size);i++)
	{
		cliente[i] = cliente[i + 1];
	}
	(*size)--;

	if (*size > 0)
	{
		Cliente * aux = realloc(cliente, (*size) * sizeof(Cliente));
		if (aux != NULL) {
			cliente = aux;
		}
	}
	else
	{
		free(cliente);
			cliente = NULL;
	}
	return cliente;


}