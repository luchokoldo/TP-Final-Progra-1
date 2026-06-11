#include <stdio.h>
#include <stdlib.h>
#include "clase.h"
#include "scanner.h"
#include "utilidades.h"

Clase* ClaseAgregarClase(Clase* clases, int* size)
{
	Clase nuevo;

	printf("\nIngrese el nombre: ");
	ScannerString(nuevo.nombre, GET_CHARSMAX(nuevo.nombre));

	printf("\nIngrese el id : ");
	nuevo.id = ScannerInt();

	printf("Ingrese el precio:$ ");
	nuevo.precio = ScannerDouble();

	printf("Ingrese la hora de inicio: ");
	nuevo.inicio.horas = ScannerInt();

	printf("Ingrese minutos: ");
	nuevo.inicio.minutos = ScannerInt();
	nuevo.inicio.esValido = 1;

	printf("Ingrese la duracion en horas: ");
	nuevo.duracion.horas = ScannerInt();

	printf("Ingrese la duracion en minutos: ");
	nuevo.duracion.minutos = ScannerInt();
	nuevo.duracion.esValido = 1;

	nuevo.idClientesValidos = 0;
	nuevo.idEntrenador = -1; 
	nuevo.idSector = -1;

	Clase* aux = NULL;

	if (clases == NULL)
	{
		aux = calloc(1, sizeof(Clase));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Clase)) devolvio NULL");

			return NULL;
		}
	}
	else
	{
		aux = realloc(clases, (*size + 1) * sizeof(Clase));

		if (aux == NULL)
		{
			printf("[ERROR] realloc(clases, (*size + 1) * sizeof(Clase)) devolvio NULL");

			return NULL;
		}
	}
	aux[*size] = nuevo;

	(*size)++;

	return aux;
}

void ClaseMostrarClase(Clase* clases, int size)
{
	if (size <= 0)
	{
		return;
	}

	ClaseMostrarClase(clases, size - 1);

	printf("-------------------------------------\n");
	printf("\nId de la clase: %d", clases[size-1].id);
	printf("\n Clase: %s", clases[size - 1].nombre);
	printf("\n Id entrenador: %d", clases[size - 1].idEntrenador);
	printf("\n Id sector: %d ", clases[size - 1].idSector);
	printf("\nClientes: ");

	if (clases[size - 1].idClientesValidos > 0)
	{
		for (int j = 0; j < clases[size - 1].idClientesValidos; j++)
		{
			printf("%d,", clases[size - 1].idClientes[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clientes asignados.\n");
	}
	printf("\n--------------------------------------\n");
}

int ClaseBuscarClaseId(Clase* clase, int size, int id,int i)
{
	if (i >= size)
	{
		return -1;
	}
	
	if (clase[i].id == id)
	{
		return i;
	}

	i++;

	return ClaseBuscarClaseId(clase,size,id,i);
}

void ClaseModificarClase(Clase* clase, int size, int id)
{
	int posicion = ClaseBuscarClaseId(clase, size, id, 0);

	if (posicion == -1)
	{
		printf("No se encontro ninguna clase con el ID: %d\n", id);

		return;
	}

	
	printf("\n---Modificando Clase ID: %d ---", id);
	printf("\nNombre actual: %s", clase[posicion].nombre);
	printf("\nPrecio actual: %.2f", clase[posicion].precio);
	printf("\nHorario de inicio actual: %02d:%02d", clase[posicion].inicio.horas, clase[posicion].inicio.minutos);
	printf("\nDuracion actual: %02d:%02d hs\n", clase[posicion].duracion.horas, clase[posicion].duracion.minutos);
	printf("---------------------------------------\n");

	
	printf("\nIngrese el nuevo nombre: ");
	ScannerString(clase[posicion].nombre, GET_CHARSMAX(clase[posicion].nombre));

	printf("Ingrese el nuevo precio: ");
	clase[posicion].precio = ScannerDouble(); 
	
	printf("Ingrese nueva hora de inicio: ");
	clase[posicion].inicio.horas = ScannerInt(); 

	printf("Ingrese nuevos minutos de inicio: ");
	clase[posicion].inicio.minutos = ScannerInt();

	clase[posicion].inicio.esValido = 1;

	
	printf("Ingrese nuevas horas de duracion: ");
	clase[posicion].duracion.horas = ScannerInt();

	printf("Ingrese nuevos minutos de duracion: ");
	clase[posicion].duracion.minutos = ScannerInt();

	clase[posicion].duracion.esValido = 1; 

	printf("Clase, horarios y duracion actualizados con exito\n");
}

Clase *ClaseEliminarClase(Clase* clases, int* size, int id)
{
	int posicion = ClaseBuscarClaseId(clases, *size, id, 0);

	if (posicion == -1)
	{
		printf("\nNo se encontro la clase con el id: %d", id);

			return clases;
	}

	if (*size > 1)
	{
		for (int i = posicion; i < (*size)-1; i++)
		{
			clases[i] = clases[i + 1];
		}
	}
	else
	{
		free(clases);

		return NULL;
	}

	(*size)--;

	Clase* aux = realloc(clases, (*size) * sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(clase, (*size) * sizeof(Clase)) devolvio NULL");

		return NULL;
	}

	return aux;
}