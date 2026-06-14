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
	char nombre[MAX_NOMBRE_SECTOR_SIZE];

	do
	{
		GymIngresarNombre(nombre, MAX_NOMBRE_SECTOR_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	Sector* temp = SectorAgregarSector(gym->sectores, gym->sectoresSize, gym->ids.sector + 1, nombre);

	if (temp == NULL)
	{
		GymExit(gym);
	}

	gym->sectores = temp;
	gym->sectoresSize++;
	gym->ids.sector++;

	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, gym->ids.sector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, gym->ids.sector)  devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoAgregarSector(sector);
	ArchivoActualizarIds(&gym->ids);
}

void GymModificarSectorNombre(Gym* gym, int id)
{
	char nombreViejo[MAX_NOMBRE_SECTOR_SIZE];
	char nombreNuevo[MAX_NOMBRE_SECTOR_SIZE];

	SectorObtenerSectorNombre(gym->sectores, gym->sectoresSize, id, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_SECTOR_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	SectorModificarSectorNombre(gym->sectores, gym->sectoresSize, id, nombreNuevo);

	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, id);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, id)  devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarSector(sector);
}

void GymObtenerSectoresNombresIds(Gym* gym, char nombresSectores[][MAX_NOMBRE_SECTOR_SIZE], int* idsSectores)
{
	SectorObtenerSectoresNombresIds(gym->sectores, gym->sectoresSize, nombresSectores, idsSectores);
}

void GymMostrarSectores(Gym* gym)
{
	SectorMostrarSectores(gym->sectores, gym->sectoresSize);
}

void GymEliminarSector(Gym* gym, int id)
{
	Sector* temp = NULL;

	temp = SectorEliminarSector(gym->sectores, gym->sectoresSize, id);

	if (temp == gym->sectores)
	{
		GymExit(gym);
	}

	if (temp == NULL)
	{
		if (gym->sectoresSize - 1 <= 0)
		{
			gym->sectores = NULL;
			gym->sectoresSize = 0;

			ArchivoBorrarSectores();

			return;
		}
		else
		{
			GymExit(gym);
		}
	}

	gym->sectores = temp;
	gym->sectoresSize--;

	ArchivoBorrarSector(id);
}

int GymHaySectores(Gym* gym)
{
	if (gym->sectores == NULL)
	{
		return 0;
	}

	return gym->sectoresSize;
}

void GymAgregarClase(Gym* gym)
{
}
void GymModificarClaseNombre(Gym* gym, int id)
{
	char nombreViejo[MAX_NOMBRE_CLASE_SIZE];
	char nombreNuevo[MAX_NOMBRE_CLASE_SIZE];

	ClaseObtenerClaseNombre(gym->clases, gym->clasesSize, id, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_CLASE_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	ClaseModificarClaseNombre(gym->clases, gym->clasesSize, id, nombreNuevo);

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, id);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, id) devolvio NULL\n");
		GymExit(gym);
		return;
	}

	ArchivoModificarClase(clase);
}

void GymEliminarClasePrecio(Gym* gym, int id)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, id);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, id) devolvio NULL\n");
		return;
	}

	ClaseEliminarPrecio(gym->clases, gym->clasesSize, id);

	ArchivoModificarClase(clase);
}

void GymObtenerClasesNombresIds(Gym* gym, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases)
{
	ClaseObtenerClasesNombresIds(gym->clases, gym->clasesSize, nombresClases, idsClases);
}

void GymMostrarClases(Gym* gym)
{
	ClaseMostrarClases(gym->clases, gym->clasesSize);
}

void GymEliminarClase(Gym* gym, int id)
{
	Clase* temp = NULL;

	temp = ClaseEliminarClase(gym->clases, &gym->clasesSize, id);

	if (temp == gym->clases && gym->clasesSize > 0)
	{
		GymExit(gym);
	}

	if (temp == NULL)
	{
		if (gym->clasesSize <= 0)
		{
			gym->clases = NULL;
			gym->clasesSize = 0;

			ArchivoBorrarClases();

			return;
		}
		else
		{
			GymExit(gym);
		}
	}

	gym->clases = temp;

	ArchivoBorrarClase(id);
}

void GymAsignarEntrenadorClase(Gym* gym, int idClase, int idEntrenador)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase con ID %d para asignar entrenador.\n", idClase);
		return;
	}

	ClaseAsignarEntrenador(clase, idEntrenador);

	ArchivoModificarClase(clase);
}

void GymEliminarEntrenadorClase(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase con ID %d para remover entrenador.\n", idClase);
		return;
	}

	ClaseEliminarEntrenador(clase);

	ArchivoModificarClase(clase);
}

void GymAsignarSectorClase(Gym* gym, int idClase, int idSector)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase con ID %d para asignar sector.\n", idClase);
		return;
	}

	ClaseAsignarSector(clase, idSector);

	ArchivoModificarClase(clase);
}

void GymEliminarSectorClase(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase con ID %d para remover sector.\n", idClase);
		return;
	}

	ClaseEliminarSector(clase);

	ArchivoModificarClase(clase);
}

int GymHayClases(Gym* gym)
{
	if (gym->clases == NULL)
	{
		return 0;
	}

	return gym->clasesSize;
}

void GymAgregarCliente(Gym* gym)
{
	char nombre[MAX_NOMBRE_CLIENTE_SIZE];
	char genero[MAX_GENERO_CLIENTE_SIZE];

	do
	{
		GymIngresarNombre(nombre, MAX_NOMBRE_CLIENTE_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	do
	{
		GymIngresarGenero(genero, MAX_GENERO_CLIENTE_SIZE);

		if (*genero == '\0')
		{
			printf("[ERROR] El genero no puede estar vacio\n");
		}
	} while (*genero == '\0');


	Cliente* temp = ClienteAgregarCliente(gym->clientes, gym->clientesSize, gym->ids.cliente + 1, nombre, genero);

	if (temp == NULL)
	{
		GymExit(gym);
	}

	gym->clientes = temp;
	gym->clientesSize++;
	gym->ids.cliente++;

	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, gym->ids.cliente);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, gym->ids.cliente) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoAgregarCliente(cliente);
	ArchivoActualizarIds(&gym->ids);
}

void GymModificarClienteNombre(Gym* gym, int id)
{
	char nombreViejo[MAX_NOMBRE_CLIENTE_SIZE];
	char nombreNuevo[MAX_NOMBRE_CLIENTE_SIZE];

	ClienteObtenerClienteNombre(gym->clientes, gym->clientesSize, id, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_CLIENTE_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	ClienteModificarClienteNombre(gym->clientes, gym->clientesSize, id, nombreNuevo);

	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, id);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarCliente(cliente);
}

void GymModificarClienteGenero(Gym* gym, int id)
{
	char generoViejo[MAX_GENERO_CLIENTE_SIZE];
	char generoNuevo[MAX_GENERO_CLIENTE_SIZE];

	ClienteObtenerClienteGenero(gym->clientes, gym->clientesSize, id, generoViejo);
	GymModificarGenero(generoViejo, generoNuevo, MAX_GENERO_CLIENTE_SIZE);

	if (*generoNuevo == '\0' || strcmp(generoNuevo, generoViejo) == 0)
	{
		return;
	}

	ClienteModificarClienteGenero(gym->clientes, gym->clientesSize, id, generoNuevo);

	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, id);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarCliente(cliente);
}

void GymObtenerClientesNombresIds(Gym* gym, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes)
{
	ClienteObtenerClientesNombresIds(gym->clientes, gym->clientesSize, nombresClientes, idsClientes);
}

void GymMostrarClientes(Gym* gym)
{
	ClienteMostrarClientes(gym->clientes, gym->clientesSize);
}

void GymEliminarCliente(Gym* gym, int id)
{
	Cliente* temp = NULL;

	temp = ClienteEliminarCliente(gym->clientes, gym->clientesSize, id);

	if (temp == gym->clientes)
	{
		GymExit(gym);
	}

	if (temp == NULL)
	{
		if (gym->clientesSize - 1 <= 0)
		{
			gym->clientes = NULL;
			gym->clientesSize = 0;

			ArchivoBorrarClientes();

			return;
		}
		else
		{
			GymExit(gym);
		}
	}

	gym->clientes = temp;
	gym->clientesSize--;

	ArchivoBorrarCliente(id);
}

void GymAgregarClienteClase(Gym* gym, int idCliente, int idClase)
{
	Cliente* cliente = ClienteBuscarClienteId(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		return;
	}

	ClienteAgregarClase(cliente, idClase);

	ArchivoModificarCliente(cliente);
}

void GymEliminarClienteClase(Gym* gym, int idCliente, int idClase)
{
	Cliente* cliente = ClienteBuscarClienteId(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		return;
	}

	ClienteEliminarClase(cliente, idClase);

	ArchivoModificarCliente(cliente);
}

int GymHayClientes(Gym* gym)
{
	if (gym->clientes == NULL)
	{
		return 0;
	}

	return gym->clientesSize;
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