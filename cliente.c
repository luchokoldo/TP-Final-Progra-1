#include <stdio.h>
#include "cliente.h"


void ClienteMostrarCliente(Cliente* clientes, int size)
{
	printf("\tLista de clientes");
	for (int i = 0; i < size; i++)
	{
		printf("\n--------------------------------------\n");
		printf("\nID: %d", clientes[i].id);
		printf("\nNombre: %s", clientes[i].nombre);
		printf("\nGenero: %s", clientes[i].genero);
		printf("\nClases: ");
		for (int z = 0; z < clientes[i].idClasesValidos; z++)
		{
			printf("%d, ", clientes[i].idClases[z]);

		}
		printf("\b\b.\n");
		printf("\n--------------------------------------\n");
	}
}