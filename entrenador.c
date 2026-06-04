#include <stdio.h>
#include "entrenador.h"


void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size)
{
	printf("---Lista De Entrenadores---\n");
	for (int i = 0; i < size; i++)
	{
		printf("\n--------------------------------------");
		printf("\n ID: %d", entrenadores[i].id);
		printf("\n Nombre: %s", entrenadores[i].nombre);
		printf("\n Genero: %s", entrenadores[i].genero);
		printf("\n--------------------------------------\n");
	}

}
