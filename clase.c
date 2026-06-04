#include <stdio.h>
#include "clase.h"


void ClaseMostrarClase(Clase* clases, int size)
{
	printf("Lista de clases\n");
	for (int i = 0; i < size; i++)
	{
		printf("-------------------------------------\n");
		printf("\nId de la clase: %d", clases[i].id);
		printf("\n Clase: %s", clases[i].nombre);
		printf("\n Id entrenador: %d", clases[i].idEntrenador);
		printf("\n Id sector: %d ", clases[i].idSector);

		for (int j = 0; j < clases[i].idClientesValidos;j++)
		{
			printf("%d,", clases[i].idClientes[j]);
		}
		printf("\b\b.\n");
		printf("\n--------------------------------------\n");

	}

}