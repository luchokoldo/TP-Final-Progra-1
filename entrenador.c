#include <stdio.h>
#include <stdlib.h>
#include "entrenador.h"
#include "scanner.h"
#include "utilidades.h"

Entrenador* EntrenadorAgregarEntrenador(Entrenador* entrenadores, int* size)
{
	Entrenador nuevo;

	printf("\nIngrese ID: ");
	nuevo.id = ScannerInt();
	printf("\nIngrese nombre: ");
	ScannerString(&nuevo.nombre, GET_CHARSMAX(nuevo.nombre));
	printf("Ingrese genero: ");
	ScannerString(nuevo.genero, GET_CHARSMAX(nuevo.genero));
	Entrenador* aux = realloc(entrenadores, (*size + 1) * sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("Error de memoria\n");
		return entrenadores;
	}

	aux[*size] = nuevo;

	(*size)++;

	return aux;
}
void EntrenadorMostrarEntrenadores(Entrenador* entrenadores, int size)
{
	if( size<=0)
	{ 
	printf("---Lista De Entrenadores---\n");
	return;
	}
	EntrenadorMostrarEntrenadores(entrenadores, size - 1);
	
		printf("\n--------------------------------------");
		printf("\n ID: %d", entrenadores[size-1].id);
		printf("\n Nombre: %s", entrenadores[size-1].nombre);
		printf("\n Genero: %s", entrenadores[size-1].genero);
		printf("\n--------------------------------------\n");
	

}

int EntrenadorBuscarEntrenadorId(Entrenador* entrenador, int size, int id, int i)
{

	if (i >= size)
	{
		return -1;
	}
	if (entrenador[i].id == id)
	{
		return i;
	}
	i++;
	return EntrenadorBuscarEntrenadorId(entrenador, size, id, i);
}
void EntrenadorModificarEntrenador(Entrenador* entrenador, int size, int id)
{
	int posicion = EntrenadorBuscarEntrenadorId(entrenador, size, id, 0);
	if (posicion == -1)
	{
		printf("\nno se encontro el entrenador con el id: %d\n", id);
		return;
	}
	printf("--Modificar entrenador con el Id: %d--\n", id);
	printf("\nNombre del entrenador: %s", entrenador[posicion].nombre);
	printf("\nGenero: %s", entrenador[posicion].genero);
	printf("-------------------------------------------------\n");

	printf("\nIngrese el nuevo nombre del entrenador: ");
	ScannerString(entrenador[posicion].nombre,GET_CHARSMAX(entrenador[posicion].nombre));

	printf("\n Nombre cambiado con Exito");

}
