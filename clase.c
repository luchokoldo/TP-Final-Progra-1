#include <stdio.h>
#include <stdlib.h>
#include "clase.h"
#include "scanner.h"
#include "utilidades.h"

static int ClaseBuscarId(Clase* clase, int size, int idClase, int i);

Clase* ClaseAgregarClase(Clase* clases, int size, int idClase, char* nombre, double precio, Horario inicio, Duracion duracion)
{
	Clase nuevo = { 0 };

	nuevo.id = idClase;
	snprintf(nuevo.nombre, MAX_NOMBRE_CLASE_SIZE, "%s", nombre);
	nuevo.precio = precio;
	nuevo.inicio = inicio;
	nuevo.duracion= duracion;
	nuevo.idClientesValidos = 0;
	nuevo.idEntrenador = CLASE_ID_INVALIDO; 
	nuevo.idSector = CLASE_ID_INVALIDO;

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

void ClaseMostrarClases(Clase* clases, int size)
{
	if (size <= 0)
	{
		return;
	}

	ClaseMostrarClases(clases, size - 1);

	printf("\n-------------------------------------\n\n");
	printf("Id de la clase: %d\n", clases[size-1].id);
	printf("Clase: %s\n", clases[size - 1].nombre);
	printf("Id entrenador: %d\n", clases[size - 1].idEntrenador);
	printf("Id sector: %d\n", clases[size - 1].idSector);
	printf("Clientes: ");

	if (clases[size - 1].idClientesValidos > 0)
	{
		for (int j = 0; j < clases[size - 1].idClientesValidos; j++)
		{
			printf("%d, ", clases[size - 1].idClientes[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clientes asignados.\n");
	}

	printf("Hora de inicio: %02d:%02d\n", clases[size - 1].inicio.horas, clases[size - 1].inicio.minutos);
	printf("Duracion: %02d:%02d\n", clases[size - 1].duracion.horas, clases[size - 1].duracion.minutos);

	printf("\n--------------------------------------\n");
}

void ClaseMostrarClase(Clase* clase)
{
	printf("\n-------------------------------------\n\n");
	printf("Id de la clase: %d\n", clase->id);
	printf("Clase: %s\n", clase->nombre);
	printf("Id entrenador: %d\n", clase->idEntrenador);
	printf("Id sector: %d\n", clase->idSector);
	printf("Clientes: ");

	if (clase->idClientesValidos > 0)
	{
		for (int j = 0; j < clase->idClientesValidos; j++)
		{
			printf("%d, ", clase->idClientes[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clientes asignados.\n");
	}

	printf("Hora de inicio: %02d:%02d\n", clase->inicio.horas, clase->inicio.minutos);
	printf("Duracion: %02d:%02d\n", clase->duracion.horas, clase->duracion.minutos);

	printf("\n--------------------------------------\n");
}

int ClaseBuscarClaseId(Clase* clases, int size, int idClase)
{
	if (idClase < 0)
	{
		return CLASE_ID_INVALIDO;
	}

	return ClaseBuscarId(clases, size, idClase, 0);
}

Clase* ClaseEliminarClase(Clase* clases, int size, int idClase)
{
	int posicion = ClaseBuscarClaseId(clases, size, idClase);

	if (posicion == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro la clase con el id: %d\n", idClase);

		return NULL;
	}

	if (size > 1)
	{
		for (int i = posicion; i < size - 1; i++)
		{
			clases[i] = clases[i + 1];
		}
	}
	else
	{
		free(clases);

		return NULL;
	}

	size--;

	Clase* aux = realloc(clases, size * sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(clase, size * sizeof(Clase)) devolvio NULL\n");

		return NULL;
	}

	return aux;
}

Clase* ClaseObtenerClase(Clase* clases, int size, int idClase)
{
	int index = ClaseBuscarClaseId(clases, size, idClase);

	if (index == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", idClase);

		return NULL;
	}

	return &clases[index];
}

void ClaseObtenerClaseNombre(Clase* clases, int size, int idClase, char* nombre)
{
	int index = ClaseBuscarClaseId(clases, size, idClase);

	if (index == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", idClase);

		return;
	}

	snprintf(nombre, MAX_NOMBRE_CLASE_SIZE, "%s", clases[index].nombre);
}

void ClaseObtenerClasesNombresIds(Clase* clases, int size, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresClases[i], MAX_NOMBRE_CLASE_SIZE, "%s", clases[i].nombre);
		idsClases[i] = clases[i].id;
	}
}

void ClaseAgregarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL)
	{
		return;
	}

	if (clase->idClientesValidos >= MAX_ID_CLIENTE_SIZE)
	{
		printf("[ERROR] La clase '%s' ya alcanzo el limite maximo de clientes (%d)\n",clase->nombre, MAX_ID_CLIENTE_SIZE);

		return;
	}

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			printf("[ERROR] El cliente con ID %d ya se encuentra inscrito en esta clase\n", idCliente);

			return;
		}
	}

	clase->idClientes[clase->idClientesValidos] = idCliente;
	clase->idClientesValidos++;
}

void ClaseEliminarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL || clase->idClientesValidos == 0)
	{
		printf("[ERROR] La clase no contiene clientes inscriptos\n");

		return;
	}

	int posicion = CLASE_ID_INVALIDO;

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			posicion = i;

			break;
		}
	}

	if (posicion == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro al cliente %d en la clase '%s'\n", idCliente, clase->nombre);

		return;
	}

	for (int i = posicion; i < clase->idClientesValidos - 1; i++)
	{
		clase->idClientes[i] = clase->idClientes[i + 1];
	}

	clase->idClientesValidos--;
}


void ClaseAsignarEntrenador(Clase* clase, int idEntrenador)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idEntrenador = idEntrenador;
}

void ClaseEliminarEntrenador(Clase* clase)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idEntrenador = CLASE_ID_INVALIDO;
}

void ClaseAsignarSector(Clase* clase, int idSector)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idSector = idSector;
}

void ClaseEliminarSector(Clase* clase)
{
	if (clase == NULL)
	{
		return;
	}

	clase->idSector = CLASE_ID_INVALIDO;
}

void ClaseModificarClaseNombre(Clase* clases,int size, int idClase, char* nombreNuevo)
{
	int index = ClaseBuscarClaseId(clases, size, idClase);

	if (index == CLASE_ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", idClase);

		return;
	}

	snprintf(clases[index].nombre, MAX_NOMBRE_CLASE_SIZE, "%s", nombreNuevo);
}

Horario ClaseObtenerClaseHorario(Clase* clase)
{
	return clase->inicio;
}

void ClaseModificarClaseHorario(Clase* clase, Horario horarioNuevo)
{
	clase->inicio = horarioNuevo;
}

Duracion ClaseObtenerClaseDuracion(Clase* clase)
{
	return clase->duracion;
}

void ClaseModificarClaseDuracion(Clase* clase, Duracion duracionNueva)
{
	clase->duracion = duracionNueva;
}

void ClaseAsignarPrecio(Clase* clase, double precioNuevo)
{
	clase->precio = precioNuevo;
}

double ClaseObtenerClasePrecio(Clase* clase)
{
	return clase->precio;
}

int ClaseObtenerClientesEnClase(Clase* clase)
{
	return clase->idClientesValidos;
}

void ClaseObtenerClaseClientesIds(Clase* clase, int* idsClientes)
{
	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		idsClientes[i] = clase->idClientes[i];
	}
}

static int ClaseBuscarId(Clase* clases, int size, int idClase, int i)
{
	if (i == size)
	{
		return CLASE_ID_INVALIDO;
	}

	if (clases[i].id == idClase)
	{
		return i;
	}

	i++;

	return ClaseBuscarId(clases, size, idClase, i);
}