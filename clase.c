#include <stdio.h>
#include <stdlib.h>
#include "clase.h"
#include "scanner.h"
#include "utilidades.h"

Clase* ClaseAgregarClase(Clase* clases, int size, int id,char* nombre, double precio, Horario inicio, Duracion duracion)
{
	Clase nuevo = { 0 };

	nuevo.id = id;
	snprintf(nuevo.nombre, MAX_NOMBRE_CLASE_SIZE, "%s", nombre);
	nuevo.precio = precio;
	nuevo.inicio = inicio;
	nuevo.duracion=duracion ;

	nuevo.idClientesValidos = 0;
	nuevo.idEntrenador = -1; 
	nuevo.idSector = -1;

	Clase* aux = NULL;

		aux = realloc(clases, (size_t)(size + 1) * sizeof(Clase));

		if (aux == NULL)
		{
			printf("[ERROR] realloc(clases, (size_t)(size + 1) * sizeof(Clase)) devolvio NULL");

			return NULL;
		}
	
	aux[size] = nuevo;

	
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

int ClaseBuscarId(Clase* clase, int size, int id,int i)
{
	if (id < 0 || id >= size)
	{
		return CLASE_ID_INVALIDO;
	}

	return ClaseBuscarId(clase, size, id, 0);

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
void ClaseAgregarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL)
	{
		return;
	}

	if (clase->idClientesValidos >= MAX_ID_CLIENTE_SIZE)
	{
		printf("[ERROR] La clase '%s' ya alcanzo el limite maximo de clientes (%d).\n",clase->nombre, MAX_ID_CLIENTE_SIZE);

		return;
	}

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			printf("El cliente con ID %d ya se encuentra inscrito en esta clase.\n", idCliente);

			return;
		}
	}

	clase->idClientes[clase->idClientesValidos] = idCliente;
	clase->idClientesValidos++;

	printf("Cliente %d agregado a la clase '%s'.\n", idCliente, clase->nombre);
}

void ClaseEliminarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL || clase->idClientesValidos == 0)
	{
		printf("La clase no contiene clientes inscriptos.\n");

		return;
	}

	int posicion = -1;

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			posicion = i;

			break;
		}
	}

	if (posicion == -1)
	{
		printf("No se encontro al cliente %d en la clase '%s'.\n", idCliente, clase->nombre);

		return;
	}

	for (int i = posicion; i < clase->idClientesValidos - 1; i++)
	{
		clase->idClientes[i] = clase->idClientes[i + 1];
	}

	clase->idClientesValidos--;

	printf("Cliente %d eliminado con exito de la clase '%s'.\n", idCliente, clase->nombre);
}


void ClaseAgregarEntrenador(Clase* clase, int idEntrenador)
{
	if (clase == NULL) return;

	if (clase->idEntrenador != -1)
	{
		printf("La clase '%s' ya tiene asignado al entrenador ID: %d. Use modificar si desea cambiarlo.\n",clase->nombre, clase->idEntrenador);

		return;
	}

	clase->idEntrenador = idEntrenador;

	printf("Entrenador %d asignado exitosamente a la clase '%s'.\n", idEntrenador, clase->nombre);
}

void ClaseModificarEntrendor(Clase* clase, int idEntrenador)
{
	if (clase == NULL) return;

	clase->idEntrenador = idEntrenador;

	printf("Entrenador de la clase '%s' actualizado con exito al ID: %d.\n", clase->nombre, idEntrenador);
}

void ClaseEliminarEntrenador(Clase* clase, int idEntrenador)
{
	if (clase == NULL) return;

	if (clase->idEntrenador == -1)
	{
		printf("La clase '%s' no tiene ningun entrenador asignado actualmente.\n", clase->nombre);

		return;
	}

	if (clase->idEntrenador != idEntrenador)
	{
		printf("El ID %d no coincide con el entrenador actual de la clase.\n", idEntrenador);

		return;
	}

	clase->idEntrenador = -1;

	printf("Entrenador removido de la clase '%s' con exito.\n", clase->nombre);
}

void ClaseAgregarSector(Clase* clase, int idSector)
{
	if (clase == NULL)
	{
		return;
	}

	if (clase->idSector != -1)
	{
		printf("La clase '%s' ya tiene asignado el sector ID: %d.\n", clase->nombre, clase->idSector);
		return;
	}

	clase->idSector = idSector;

	printf("Sector %d asignado exitosamente a la clase '%s'.\n", idSector, clase->nombre);
}

void ClaseModificarSector(Clase* clase, int idSector)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idSector = idSector;

	printf("Sector de la clase '%s' modificado con exito al ID: %d.\n", clase->nombre, idSector);
}

void ClaseEliminarSector(Clase* clase, int idSector)
{
	if (clase == NULL)
	{
		return;
	}

	if (clase->idSector == -1)
	{
		printf("La clase '%s' no tiene ningun sector asignado actualmente.\n", clase->nombre);

		return;
	}

	if (clase->idSector != idSector)
	{
		printf("El ID %d no coincide con el sector actual de la clase.\n", idSector);

		return;
	}

	clase->idSector = -1;

	printf("Sector removido de la clase '%s' con exito.\n", clase->nombre);
}