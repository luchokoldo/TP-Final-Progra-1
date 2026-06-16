#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clase.h"
#include "scanner.h"
#include "utilidades.h"

static int ClaseBuscarId(Clase* clases, int size, int idClase, int i);
static int ClaseBuscarEntrenadorId(Clase* clases, int size, int idEntrenador, int i);
static int ClaseBuscarSectorId(Clase* clases, int size, int idSector, int i);
static int ClaseChequearHorarioDuracion(Clase* clase, int idEntrenador, int idSector, Horario horario, Duracion duracion);
static void ClaseOrdenarClaseNueva(Clase* clases, int size);
static void ClaseIntercambiarClases(Clase* claseActual, Clase* claseAnterior);

Clase* ClaseAgregarClase(Clase* clases, int size, int idClase, char* nombre, int idEntrenador, int idSector, double precio, Horario inicio, Duracion duracion)
{
	Clase nuevo = { 0 };

	nuevo.id = idClase;
	snprintf(nuevo.nombre, MAX_NOMBRE_SIZE, "%s", nombre);
	nuevo.idEntrenador = idEntrenador;
	nuevo.idSector = idSector;
	nuevo.precio = precio;
	nuevo.inicio = inicio;
	nuevo.duracion= duracion;
	nuevo.idClientesValidos = 0;

	Clase* aux = NULL;

	aux = realloc(clases, (size_t)(size + 1) * sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] realloc(clases, (size_t)(size + 1) * sizeof(Clase)) devolvio NULL");

		return NULL;
	}
	
	aux[size] = nuevo;

	ClaseOrdenarClaseNueva(aux, size);

	return aux;
}

int ClaseBuscarClaseId(Clase* clases, int size, int idClase)
{
	if (idClase < 0)
	{
		return ID_INVALIDO;
	}

	return ClaseBuscarId(clases, size, idClase, 0);
}

int ClaseBuscarClaseEntrenadorId(Clase* clases, int size, int idEntrenador)
{
	if (idEntrenador < 0)
	{
		return ID_INVALIDO;
	}

	return ClaseBuscarEntrenadorId(clases, size, idEntrenador, 0);
}

int ClaseBuscarClaseSectorId(Clase* clases, int size, int idSector)
{
	if (idSector < 0)
	{
		return ID_INVALIDO;
	}

	return ClaseBuscarSectorId(clases, size, idSector, 0);
}

Clase* ClaseEliminarClase(Clase* clases, int size, int idClase)
{
	int posicion = ClaseBuscarClaseId(clases, size, idClase);

	if (posicion == ID_INVALIDO)
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

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", idClase);

		return NULL;
	}

	return &clases[index];
}

void ClaseObtenerClaseNombre(Clase* clase, char* nombreClase)
{
	snprintf(nombreClase, MAX_NOMBRE_SIZE, "%s", clase->nombre);
}

void ClaseObtenerClasesNombresIds(Clase* clases, int size, char nombresClases[][MAX_NOMBRE_SIZE], int* idsClases)
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresClases[i], MAX_NOMBRE_SIZE, "%s", clases[i].nombre);
		idsClases[i] = clases[i].id;
	}
}

void ClaseObtenerClasesIds(Clase* clases, int size, int* idsClases)
{
	for (int i = 0; i < size; i++)
	{
		idsClases[i] = clases[i].id;
	}
}

void ClaseObtenerClasesNombres(Clase* clases, int size, char nombresClases[][MAX_NOMBRE_SIZE])
{
	for (int i = 0; i < size; i++)
	{
		snprintf(nombresClases[i], MAX_NOMBRE_SIZE, "%s", clases[i].nombre);
	}
}

void ClaseObtenerClasesEntrenadores(Clase* clases, int size, int* idsClasesEntrenadores)
{
	for (int i = 0; i < size; i++)
	{
		idsClasesEntrenadores[i] = clases[i].idEntrenador;
	}
}

void ClaseObtenerClasesSectores(Clase* clases, int size, int* idsClasesSectores)
{
	for (int i = 0; i < size; i++)
	{
		idsClasesSectores[i] = clases[i].idSector;
	}
}

void ClaseObtenerClasesClientes(Clase* clases, int size, int idsClasesClientes[][MAX_IDS], int* clasesClientesValidos)
{
	for (int i = 0; i < size; i++)
	{
		clasesClientesValidos[i] = clases[i].idClientesValidos;

		for (int j = 0; j < clasesClientesValidos[i]; j++)
		{
			idsClasesClientes[i][j] = clases[i].idClientes[j];
		}		
	}
}

void ClaseObtenerClasesPrecios(Clase* clases, int size, double* preciosClases)
{
	for (int i = 0; i < size; i++)
	{
		preciosClases[i] = clases[i].precio;
	}
}

void ClaseObtenerClasesHorarios(Clase* clases, int size, int* clasesHorariosHoras, int* clasesHorariosMinutos)
{
	for (int i = 0; i < size; i++)
	{
		clasesHorariosHoras[i] = clases[i].inicio.horas;
		clasesHorariosMinutos[i] = clases[i].inicio.minutos;
	}
}

void ClaseObtenerClasesDuracion(Clase* clases, int size, int* clasesDuracionHoras, int* clasesDuracionMinutos)
{
	for (int i = 0; i < size; i++)
	{
		clasesDuracionHoras[i] = clases[i].duracion.horas;
		clasesDuracionMinutos[i] = clases[i].duracion.minutos;
	}
}

int ClaseObtenerClaseEntrenador(Clase* clase)
{
	return clase->idEntrenador;
}

int ClaseObtenerClaseSector(Clase* clase)
{
	return clase->idSector;
}

int ClaseAgregarCliente(Clase* clase, int idCliente)
{
	if (clase->idClientesValidos >= MAX_IDS)
	{
		printf("[ERROR] La clase '%s' ya alcanzo el limite maximo de clientes (%d)\n",clase->nombre, MAX_IDS);

		return 0;
	}

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			printf("[ERROR] El cliente ya se encuentra inscrito en esta clase\n");

			return 0;
		}
	}

	clase->idClientes[clase->idClientesValidos] = idCliente;
	clase->idClientesValidos++;

	return 1;
}

void ClaseEliminarCliente(Clase* clase, int idCliente)
{
	if (clase == NULL || clase->idClientesValidos == 0)
	{
		printf("[ERROR] La clase no contiene clientes inscriptos\n");

		return;
	}

	int posicion = ID_INVALIDO;

	for (int i = 0; i < clase->idClientesValidos; i++)
	{
		if (clase->idClientes[i] == idCliente)
		{
			posicion = i;

			break;
		}
	}

	if (posicion == ID_INVALIDO)
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

	clase->idEntrenador = ID_INVALIDO;
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

	clase->idSector = ID_INVALIDO;
}

void ClaseModificarClaseNombre(Clase* clases,int size, int idClase, char* nombreNuevo)
{
	int index = ClaseBuscarClaseId(clases, size, idClase);

	if (index == ID_INVALIDO)
	{
		printf("[ERROR] No se encontro el id %d", idClase);

		return;
	}

	snprintf(clases[index].nombre, MAX_NOMBRE_SIZE, "%s", nombreNuevo);
}

Horario ClaseObtenerClaseHorario(Clase* clase)
{
	return clase->inicio;
}

void ClaseObtenerClaseHorarioInt(Clase* clase, int* horasHorario, int* minutosHorario)
{
	*horasHorario = clase->inicio.horas;
	*minutosHorario = clase->inicio.minutos;
}

void ClaseModificarClaseHorario(Clase* clase, Horario horarioNuevo)
{
	clase->inicio = horarioNuevo;
}

Duracion ClaseObtenerClaseDuracion(Clase* clase)
{
	return clase->duracion;
}

void ClaseObtenerClaseDuracionInt(Clase* clase, int* horasDuracion, int* minutosDuracion)
{
	*horasDuracion = clase->duracion.horas;
	*minutosDuracion = clase->duracion.minutos;
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

int ClaseObtenerCantidadClientesEnClase(Clase* clase)
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

int ClaseChequearClaseHorarioDuracion(Clase* clases, int size, int idClase, int idEntrenador, int idSector, Horario horario, Duracion duracion)
{
	for (int i = 0; i < size; i++)
	{
		if (clases[i].id == idClase)
		{
			continue;
		}
		
		if (ClaseChequearHorarioDuracion(&clases[i], idEntrenador, idSector, horario, duracion) == 1)
		{
			return 1;
		}
	}

	return 0;
}

void ClaseOrdenarClases(Clase* clases, int size)
{
	if (size <= 1)
	{
		return;
	}
	
	int indexMenor = 0;

	for (int i = 0; i < size; i++)
	{
		indexMenor = i;
		
		for (int j = i + 1; j < size; j++)
		{
			if (_strcmpi(clases[indexMenor].nombre, clases[j].nombre) > 0)
			{
				indexMenor = j;
			}
		}

		if (indexMenor != i)
		{
			ClaseIntercambiarClases(&clases[indexMenor], &clases[i]);
		}
	}
}

Horario ClaseCrearHorario(int horasHorario, int minutosHorario)
{
	Horario nuevo = { .horas = horasHorario, .minutos = minutosHorario, .esValido = 1 };

	return nuevo;
}

Duracion ClaseCrearDuracion(int horasDuracion, int minutosDuracion)
{
	Duracion nuevo = { .horas = horasDuracion, .minutos = minutosDuracion, .esValido = 1 };

	return nuevo;
}

static int ClaseBuscarId(Clase* clases, int size, int idClase, int i)
{
	if (i == size)
	{
		return ID_INVALIDO;
	}

	if (clases[i].id == idClase)
	{
		return i;
	}

	i++;

	return ClaseBuscarId(clases, size, idClase, i);
}

static int ClaseBuscarEntrenadorId(Clase* clases, int size, int idEntrenador, int i)
{
	if (i == size)
	{
		return ID_INVALIDO;
	}

	if (clases[i].idEntrenador == idEntrenador)
	{
		return i;
	}

	i++;

	return ClaseBuscarEntrenadorId(clases, size, idEntrenador, i);
}

static int ClaseBuscarSectorId(Clase* clases, int size, int idSector, int i)
{
	if (i == size)
	{
		return ID_INVALIDO;
	}

	if (clases[i].idSector == idSector)
	{
		return i;
	}

	i++;

	return ClaseBuscarSectorId(clases, size, idSector, i);
}

static int ClaseChequearHorarioDuracion(Clase* clase, int idEntrenador, int idSector, Horario horario, Duracion duracion)
{
	if (clase->idEntrenador == ID_INVALIDO || clase->idSector == ID_INVALIDO || (clase->idSector != idSector && clase->idEntrenador != idEntrenador))
	{
		return 0;
	}

	int inicio1 = clase->inicio.horas * 60 + clase->inicio.minutos;
	int inicio2 = horario.horas * 60 + horario.minutos;

	int fin1 = inicio1 + clase->duracion.horas * 60 + clase->duracion.minutos;
	int fin2 = inicio2 + duracion.horas * 60 + duracion.minutos;

	if (inicio1 < fin2 && inicio2 < fin1)
	{
		return 1; // Se superponen
	}

	return 0;
}

static void ClaseOrdenarClaseNueva(Clase* clases, int size)
{
	if (size < 1)
	{
		return;
	}

	if (_strcmpi(clases[size - 1].nombre, clases[size].nombre) > 0)
	{
		ClaseIntercambiarClases(&clases[size], &clases[size - 1]);
	}

	ClaseOrdenarClaseNueva(clases, size - 1);
}

static void ClaseIntercambiarClases(Clase* claseActual, Clase* claseAnterior)
{
	Clase aux = *claseActual;

	*claseActual = *claseAnterior;
	*claseAnterior = aux;
}