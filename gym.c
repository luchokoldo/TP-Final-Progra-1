#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gym.h"
#include "scanner.h"
#include "utilidades.h"
#include "archivos.h"

static void GymIngresarNombre(char* nombre, int size);
static void GymIngresarGenero(char* genero, int size);
static void GymModificarNombre(char* nombreViejo, char* nombreNuevo, int size);
static void GymModificarGenero(char* generoViejo, char* generoNuevo, int size);
static void GymLiberarMemoria(Gym* gym);
static void GymExit(Gym* gym);

void GymAgregarEntrenador(Gym* gym)
{
	char nombre[MAX_NOMBRE_ENTRENADOR_SIZE];
	char genero[MAX_GENERO_ENTRENADOR_SIZE];
	
	do
	{
		GymIngresarNombre(nombre, MAX_NOMBRE_ENTRENADOR_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	do
	{
		GymIngresarGenero(genero, MAX_GENERO_ENTRENADOR_SIZE);

		if (*genero == '\0')
		{
			printf("[ERROR] El genero no puede estar vacio\n");
		}
	} while (*genero == '\0');

	
	Entrenador* temp = EntrenadorAgregarEntrenador(gym->entrenadores, gym->entrenadoresSize, gym->ids.entrenador + 1, nombre, genero);

	if (temp == NULL)
	{
		GymExit(gym);
	}

	gym->entrenadores = temp;
	gym->entrenadoresSize++;
	gym->ids.entrenador++;

	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, gym->ids.entrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, gym->ids.entrenador) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoAgregarEntrenador(entrenador);
	ArchivoActualizarIds(&gym->ids);
}

void GymModificarEntrenadorNombre(Gym* gym, int id)
{
	char nombreViejo[MAX_NOMBRE_ENTRENADOR_SIZE];
	char nombreNuevo[MAX_NOMBRE_ENTRENADOR_SIZE];

	EntrenadorObtenerEntrenadorNombre(gym->entrenadores, gym->entrenadoresSize, id, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_ENTRENADOR_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	EntrenadorModificarEntrenadorNombre(gym->entrenadores, gym->entrenadoresSize, id, nombreNuevo);

	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, id);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, id) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarEntrenador(entrenador);
}

void GymModificarEntrenadorGenero(Gym* gym, int id)
{
	char generoViejo[MAX_GENERO_ENTRENADOR_SIZE];
	char generoNuevo[MAX_GENERO_ENTRENADOR_SIZE];

	EntrenadorObtenerEntrenadorGenero(gym->entrenadores, gym->entrenadoresSize, id, generoViejo);
	GymModificarGenero(generoViejo, generoNuevo, MAX_GENERO_ENTRENADOR_SIZE);

	if (*generoNuevo == '\0' || strcmp(generoNuevo, generoViejo) == 0)
	{
		return;
	}

	EntrenadorModificarEntrenadorGenero(gym->entrenadores, gym->entrenadoresSize, id, generoNuevo);

	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, id);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, id) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarEntrenador(entrenador);
}

void GymObtenerEntrenadoresNombresIds(Gym* gym, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores)
{
	EntrenadorObtenerEntrenadoresNombresIds(gym->entrenadores, gym->entrenadoresSize, nombresEntrenadores, idsEntrenadores);
}

void GymMostrarEntrenadores(Gym* gym)
{
	EntrenadorMostrarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
}

void GymEliminarEntrenador(Gym* gym, int id)
{
	Entrenador* temp = NULL;

	temp = EntrenadorEliminarEntrenador(gym->entrenadores, gym->entrenadoresSize, id);

	if (temp == gym->entrenadores)
	{
		GymExit(gym);
	}

	if (temp == NULL)
	{
		if (gym->entrenadoresSize - 1 <= 0)
		{
			gym->entrenadores = NULL;
			gym->entrenadoresSize = 0;

			ArchivoBorrarEntrenadores();

			return;
		}
		else
		{
			GymExit(gym);
		}		
	}

	gym->entrenadores = temp;
	gym->entrenadoresSize--;

	ArchivoBorrarEntrenador(id);
}

int GymHayEntrenadores(Gym* gym)
{
	if (gym->entrenadores == NULL)
	{
		return 0;
	}

	return gym->entrenadoresSize;
}

void GymAgregarSector(Gym* gym)
{

}

void GymAgregarClase(Gym* gym)
{

}

void GymAgregarCliente(Gym* gym)
{

}

static void GymIngresarNombre(char* nombre, int size)
{
	printf("Ingrese nombre: ");
	ScannerString(nombre, size);

	snprintf(nombre, size, "%s", UtilidadesStringTrim(nombre));
}

static void GymIngresarGenero(char* genero, int size)
{
	printf("Ingrese genero: ");
	ScannerString(genero, size);

	snprintf(genero, size, "%s", UtilidadesStringTrim(genero));
}

static void GymModificarNombre(char* nombreViejo, char* nombreNuevo, int size)
{
	printf("Nombre actual: %s\n", nombreViejo);

	printf("Ingresar nuevo nombre (vacio para cancelar): ");
	ScannerString(nombreNuevo, size);

	snprintf(nombreNuevo, size, "%s", UtilidadesStringTrim(nombreNuevo));
}

static void GymModificarGenero(char* generoViejo, char* generoNuevo, int size)
{
	printf("Genero actual: %s\n", generoViejo);

	printf("Ingresar nuevo genero (vacio para cancelar): ");
	ScannerString(generoNuevo, size);

	snprintf(generoNuevo, size, "%s", UtilidadesStringTrim(generoNuevo));
}

static void GymLiberarMemoria(Gym* gym)
{
	free(gym->entrenadores);
	free(gym->sectores);
	free(gym->clases);
	free(gym->clientes);
}

static void GymExit(Gym* gym)
{
	GymLiberarMemoria(gym);

	exit(1);
}