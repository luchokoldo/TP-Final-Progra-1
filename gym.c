#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gym.h"
#include "scanner.h"
#include "utilidades.h"
#include "archivos.h"

static void GymIngresarNombre(char* nombre, int size);
static void GymIngresarGenero(char* genero, int size);
static double GymIngresarPrecio(void);
static Horario GymIngresarHorario(void);
static Duracion GymIngresarDuracion(void);
static void GymModificarNombre(char* nombreViejo, char* nombreNuevo, int size);
static void GymModificarGenero(char* generoViejo, char* generoNuevo, int size);
static double GymModificarPrecio(double precioViejo);
static Horario GymModificarHorario(Horario horarioViejo);
static Duracion GymModificarDuracion(Duracion duracionViejo);
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

		return;
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

void GymModificarEntrenadorNombre(Gym* gym, int idEntrenador)
{
	char nombreViejo[MAX_NOMBRE_ENTRENADOR_SIZE];
	char nombreNuevo[MAX_NOMBRE_ENTRENADOR_SIZE];

	EntrenadorObtenerEntrenadorNombre(gym->entrenadores, gym->entrenadoresSize, idEntrenador, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_ENTRENADOR_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	EntrenadorModificarEntrenadorNombre(gym->entrenadores, gym->entrenadoresSize, idEntrenador, nombreNuevo);

	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarEntrenador(entrenador);
}

void GymModificarEntrenadorGenero(Gym* gym, int idEntrenador)
{
	char generoViejo[MAX_GENERO_ENTRENADOR_SIZE];
	char generoNuevo[MAX_GENERO_ENTRENADOR_SIZE];

	EntrenadorObtenerEntrenadorGenero(gym->entrenadores, gym->entrenadoresSize, idEntrenador, generoViejo);
	GymModificarGenero(generoViejo, generoNuevo, MAX_GENERO_ENTRENADOR_SIZE);

	if (*generoNuevo == '\0' || strcmp(generoNuevo, generoViejo) == 0)
	{
		return;
	}

	EntrenadorModificarEntrenadorGenero(gym->entrenadores, gym->entrenadoresSize, idEntrenador, generoNuevo);

	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL");

		GymExit(gym);

		return;
	}

	ArchivoModificarEntrenador(entrenador);
}

int GymObtenerEntrenadoresNombresIds(Gym* gym, char nombresEntrenadores[][MAX_NOMBRE_ENTRENADOR_SIZE], int* idsEntrenadores)
{
	EntrenadorObtenerEntrenadoresNombresIds(gym->entrenadores, gym->entrenadoresSize, nombresEntrenadores, idsEntrenadores);

	return gym->entrenadoresSize;
}

void GymMostrarEntrenadores(Gym* gym)
{
	EntrenadorMostrarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
}

void GymMostrarEntrenador(Gym* gym, int idEntrenador)
{
	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	EntrenadorMostrarEntrenador(entrenador);
}

void GymEliminarEntrenador(Gym* gym, int idEntrenador)
{
	Entrenador* temp = NULL;

	temp = EntrenadorEliminarEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (temp == gym->entrenadores)
	{
		GymExit(gym);

		return;
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

			return;
		}
	}

	gym->entrenadores = temp;
	gym->entrenadoresSize--;

	ArchivoBorrarEntrenador(idEntrenador);
}

void GymExportarEntrenadoresArchivoTexto(Gym* gym)
{
	ArchivoExportarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
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

		return;
	}

	gym->sectores = temp;
	gym->sectoresSize++;
	gym->ids.sector++;

	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, gym->ids.sector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, gym->ids.sector)  devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ArchivoAgregarSector(sector);
	ArchivoActualizarIds(&gym->ids);
}

void GymModificarSectorNombre(Gym* gym, int idSector)
{
	char nombreViejo[MAX_NOMBRE_SECTOR_SIZE];
	char nombreNuevo[MAX_NOMBRE_SECTOR_SIZE];

	SectorObtenerSectorNombre(gym->sectores, gym->sectoresSize, idSector, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_SECTOR_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	SectorModificarSectorNombre(gym->sectores, gym->sectoresSize, idSector, nombreNuevo);

	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector)  devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ArchivoModificarSector(sector);
}

int GymObtenerSectoresNombresIds(Gym* gym, char nombresSectores[][MAX_NOMBRE_SECTOR_SIZE], int* idsSectores)
{
	SectorObtenerSectoresNombresIds(gym->sectores, gym->sectoresSize, nombresSectores, idsSectores);

	return gym->sectoresSize;
}

void GymMostrarSectores(Gym* gym)
{
	SectorMostrarSectores(gym->sectores, gym->sectoresSize);
}

void GymMostrarSector(Gym* gym, int idSector)
{
	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector)  devolvio NULL\n");

		GymExit(gym);

		return;
	}
	
	SectorMostrarSector(sector);
}

void GymEliminarSector(Gym* gym, int idSector)
{
	Sector* temp = NULL;

	temp = SectorEliminarSector(gym->sectores, gym->sectoresSize, idSector);

	if (temp == gym->sectores)
	{
		GymExit(gym);

		return;
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

			return;
		}
	}

	gym->sectores = temp;
	gym->sectoresSize--;

	ArchivoBorrarSector(idSector);
}

void GymExportarSectoresArchivoTexto(Gym* gym)
{
	ArchivoExportarSectores(gym->sectores, gym->sectoresSize);
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
	char nombre[MAX_NOMBRE_SECTOR_SIZE];
	double precio = 0.0;
	Horario inicio = { 0 };
	Duracion duracion = { 0 };

	do
	{
		GymIngresarNombre(nombre, MAX_NOMBRE_SECTOR_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	do
	{
		precio = GymIngresarPrecio();

		if (precio < 0)
		{
			printf("[ERROR] El precio no puede ser menor a 0\n");
		}
	} while (precio < 0);

	do
	{
		inicio = GymIngresarHorario();

		inicio.horas += inicio.minutos / 60;
		inicio.minutos %= 60;

		if (inicio.horas < 0)
		{
			printf("[ERROR] La hora no pueden ser menor a 0\n");
		}
		else if (inicio.minutos < 0)
		{
			printf("[ERROR] Los minutos no pueden ser menor a 0\n");
		}
		else if (inicio.horas > 24)
		{
			printf("[ERROR] La hora no pueden ser mayor a 24\n");
		}
	} while (inicio.horas < 0 || inicio.minutos < 0 || inicio.horas > 24);

	inicio.esValido = 1;

	do
	{
		duracion = GymIngresarDuracion();

		duracion.horas += duracion.minutos / 60;
		duracion.minutos %= 60;

		if (duracion.horas < 0)
		{
			printf("[ERROR] La hora no pueden ser menor a 0\n");
		}
		else if (duracion.minutos < 0)
		{
			printf("[ERROR] Los minutos no pueden ser menor a 0\n");
		}
	} while (duracion.horas < 0 || duracion.minutos < 0);

	duracion.esValido = 1;

	Clase* temp = ClaseAgregarClase(gym->clases, gym->clasesSize, gym->ids.clase + 1, nombre, precio, inicio, duracion);

	if (temp == NULL)
	{
		GymExit(gym);

		return;
	}

	gym->clases = temp;
	gym->clasesSize++;
	gym->ids.clase++;

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, gym->ids.clase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, gym->ids.clase)  devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ArchivoAgregarClase(clase);
	ArchivoActualizarIds(&gym->ids);
}

void GymModificarClaseNombre(Gym* gym, int idClase)
{
	char nombreViejo[MAX_NOMBRE_CLASE_SIZE];
	char nombreNuevo[MAX_NOMBRE_CLASE_SIZE];

	ClaseObtenerClaseNombre(gym->clases, gym->clasesSize, idClase, nombreViejo);
	GymModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_CLASE_SIZE);

	if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
	{
		return;
	}

	ClaseModificarClaseNombre(gym->clases, gym->clasesSize, idClase, nombreNuevo);

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ArchivoModificarClase(clase);
}

void GymAsignarClasePrecio(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	double precioViejo = ClaseObtenerClasePrecio(clase);
	double precioNuevo = 0.0;

	do
	{
		precioNuevo = GymModificarPrecio(precioViejo);

		if (precioNuevo < 0 && precioNuevo != -1)
		{
			printf("[ERROR] El precio tiene que ser mayor o igual a 0\n");
		}
	} while (precioNuevo < 0 && precioNuevo != -1);

	if (precioNuevo == -1)
	{
		return;
	}

	ClaseAsignarPrecio(clase, precioNuevo);

	ArchivoModificarClase(clase);
}

void GymModificarClaseHorario(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	Horario horarioViejo = ClaseObtenerClaseHorario(clase);
	Horario horarioNuevo = { 0 };

	do
	{
		horarioNuevo = GymModificarHorario(horarioViejo);

		horarioNuevo.horas += horarioNuevo.minutos / 60;
		horarioNuevo.minutos %= 60;

		if (horarioNuevo.horas < 0)
		{
			printf("[ERROR] La hora no pueden ser menor a 0\n");
		}
		else if (horarioNuevo.minutos < 0)
		{
			printf("[ERROR] Los minutos no pueden ser menor a 0\n");
		}
		else if (horarioNuevo.horas > 24)
		{
			printf("[ERROR] La hora no pueden ser mayor a 24\n");
		}
	} while (horarioNuevo.horas < 0 || horarioNuevo.minutos < 0 || horarioNuevo.horas > 24);

	horarioNuevo.esValido = 1;

	ClaseModificarClaseHorario(clase, horarioNuevo);

	ArchivoModificarClase(clase);
}

void GymModificarClaseDuracion(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	Duracion duracionViejo = ClaseObtenerClaseDuracion(clase);
	Duracion duracionNuevo = { 0 };

	do
	{
		duracionNuevo = GymModificarDuracion(duracionViejo);

		duracionNuevo.horas += duracionNuevo.minutos / 60;
		duracionNuevo.minutos %= 60;

		if (duracionNuevo.horas < 0)
		{
			printf("[ERROR] La hora no pueden ser menor a 0\n");
		}
		else if (duracionNuevo.minutos < 0)
		{
			printf("[ERROR] Los minutos no pueden ser menor a 0\n");
		}
	} while (duracionNuevo.horas < 0 || duracionNuevo.minutos < 0);

	duracionNuevo.esValido = 1;

	ClaseModificarClaseDuracion(clase, duracionNuevo);

	ArchivoModificarClase(clase);
}

int GymObtenerClasesNombresIds(Gym* gym, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases)
{
	ClaseObtenerClasesNombresIds(gym->clases, gym->clasesSize, nombresClases, idsClases);

	return gym->clasesSize;
}

int GymObtenerClaseClientesNombresIds(Gym* gym, int idClase, char nombresClientes[MAX_ID_CLASE_SIZE][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	int idsSize = ClaseObtenerClientesEnClase(clase);

	ClaseObtenerClaseClientesIds(clase, idsClientes);

	for (int i = 0; i < idsSize; i++)
	{
		Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idClase);

		if (cliente == NULL)
		{
			printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL\n");

			GymExit(gym);

			return;
		}

		snprintf(nombresClientes[i], MAX_NOMBRE_CLIENTE_SIZE, "%s", cliente->nombre);
	}

	return idsSize;
}

void GymMostrarClases(Gym* gym)
{
	ClaseMostrarClases(gym->clases, gym->clasesSize);
}

void GymMostrarClase(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ClaseMostrarClase(clase);
}

void GymEliminarClase(Gym* gym, int idClase)
{
	int clientesSize = GymHayClientesEnClase(gym, idClase);

	if (clientesSize > 0)
	{
		Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

		if (clase == NULL)
		{
			printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

			GymExit(gym);

			return;
		}

		int idsClientes[MAX_ID_CLIENTE_SIZE] = { 0 };

		ClaseObtenerClaseClientesIds(clase, idsClientes);

		for (int i = 0; i < clientesSize; i++)
		{
			Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idsClientes[i]);

			if (cliente == NULL)
			{
				printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, idsClientes[i]) devolvio NULL\n");

				GymExit(gym);

				return;
			}

			ClienteEliminarClase(cliente, idClase);

			ArchivoModificarCliente(cliente);
		}
	}
	
	Clase* temp = NULL;

	temp = ClaseEliminarClase(gym->clases, gym->clasesSize, idClase);

	if (temp == NULL)
	{
		if (gym->clasesSize - 1 <= 0)
		{
			gym->clases = NULL;
			gym->clasesSize = 0;

			ArchivoBorrarClases();

			return;
		}
		else
		{
			GymExit(gym);

			return;
		}
	}

	gym->clases = temp;
	gym->clasesSize--;

	ArchivoBorrarClase(idClase);
}

void GymAsignarEntrenadorClase(Gym* gym, int idClase, int idEntrenador)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase con el id %d para asignar entrenador\n", idClase);

		GymExit(gym);

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

		GymExit(gym);

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

		GymExit(gym);

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

		GymExit(gym);

		return;
	}

	ClaseEliminarSector(clase);

	ArchivoModificarClase(clase);
}

void GymExportarClasesArchivoTexto(Gym* gym)
{
	ArchivoExportarClases(gym->clases, gym->clasesSize);
}

int GymHayClientesEnClase(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase %d\n", idClase);

		GymExit(gym);

		return;
	}

	return ClaseObtenerClientesEnClase(clase);
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

		return;
	}

	gym->clientes = temp;
	gym->clientesSize++;
	gym->ids.cliente++;

	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, gym->ids.cliente);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, gym->ids.cliente) devolvio NULL\n");

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
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL\n");

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
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ArchivoModificarCliente(cliente);
}

int GymObtenerClientesNombresIds(Gym* gym, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes)
{
	ClienteObtenerClientesNombresIds(gym->clientes, gym->clientesSize, nombresClientes, idsClientes);

	return gym->clientesSize;
}

int GymObtenerClienteClasesNombresIds(Gym* gym, int idCliente, char nombresClases[MAX_ID_CLASE_SIZE][MAX_NOMBRE_CLASE_SIZE], int* idsClases)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return 0;
	}

	int idsSize = ClienteObtenerClasesEnCliente(cliente);

	ClienteObtenerClienteClasesIds(cliente, idsClases);

	for (int i = 0; i < idsSize; i++)
	{
		Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idsClases[i]);

		if (clase == NULL)
		{
			printf("[ERROR] No se encontro la clase %d\n", idsClases[i]);

			GymExit(gym);

			return 0;
		}

		snprintf(nombresClases[i], MAX_NOMBRE_CLASE_SIZE, "%s", clase->nombre);
	}

	return idsSize;
}

void GymMostrarClientes(Gym* gym)
{
	char nombresClases[100][MAX_NOMBRE_CLASE_SIZE];
	int idsClases[100] = { 0 };
	int clasesSize = GymObtenerClasesNombresIds(gym, nombresClases, idsClases);

	ClienteMostrarClientes(gym->clientes, gym->clientesSize, nombresClases, idsClases, clasesSize);
}

void GymMostrarCliente(Gym* gym, int idCliente)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return;
	}
	char nombresClases[100][MAX_NOMBRE_CLASE_SIZE];
	int idsClases[100] = { 0 };
	int clasesSize = GymObtenerClasesNombresIds(gym, nombresClases, idsClases);

	ClienteMostrarCliente(cliente, nombresClases, idsClases, clasesSize);
}

void GymEliminarCliente(Gym* gym, int idCliente)
{
	int clasesSize = GymHayClasesEnCliente(gym, idCliente);

	if (clasesSize > 0)
	{
		Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

		if (cliente == NULL)
		{
			printf("[ERROR] No se encontro el cliente %d\n", idCliente);

			GymExit(gym);

			return;
		}

		int idsClases[MAX_ID_CLASE_SIZE] = { 0 };

		ClienteObtenerClienteClasesIds(cliente, idsClases);

		for (int i = 0; i < clasesSize; i++)
		{
			Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idsClases[i]);

			if (clase == NULL)
			{
				printf("[ERROR] No se encontro la clase %d\n", idsClases[i]);

				GymExit(gym);

				return;
			}
			
			ClaseEliminarCliente(clase, idCliente);

			ArchivoModificarClase(clase);
		}
	}	
	
	Cliente* temp = NULL;

	temp = ClienteEliminarCliente(gym->clientes, gym->clientesSize, idCliente);

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

			return;
		}
	}

	gym->clientes = temp;
	gym->clientesSize--;

	ArchivoBorrarCliente(idCliente);
}

void GymAgregarClienteClase(Gym* gym, int idCliente, int idClase)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return;
	}

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase %d\n", idClase);

		GymExit(gym);

		return;
	}

	ClienteAgregarClase(cliente, idClase);
	ClaseAgregarCliente(clase, idCliente);

	ArchivoModificarCliente(cliente);
	ArchivoModificarClase(clase);
}

void GymEliminarClienteClase(Gym* gym, int idCliente, int idClase)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return;
	}

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase %d\n", idClase);

		GymExit(gym);

		return;
	}

	ClienteEliminarClase(cliente, idClase);
	ClaseEliminarCliente(clase, idCliente);

	ArchivoModificarCliente(cliente);
	ArchivoModificarClase(clase);
}

void GymExportarClientesArchivoTexto(Gym* gym)
{
	ArchivoExportarClientes(gym->clientes, gym->clientesSize);
}

int GymHayClasesEnCliente(Gym* gym, int idCliente)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return;
	}
	
	return ClienteObtenerClasesEnCliente(cliente);
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

static double GymIngresarPrecio()
{
	printf("Ingrese precio: $");
	double precio = ScannerDouble();

	return precio;
}

static Horario GymIngresarHorario()
{
	Horario nuevo = { 0 };

	printf("Ingrese hora de inicio: ");
	nuevo.horas = ScannerInt();

	printf("Ingrese minuto de inicio: ");
	nuevo.minutos = ScannerInt();

	return nuevo;
}

static Duracion GymIngresarDuracion()
{
	Duracion nuevo = { 0 };

	printf("Ingrese horas de duracion: ");
	nuevo.horas = ScannerInt();

	printf("Ingrese minutos de duracion: ");
	nuevo.minutos = ScannerInt();

	return nuevo;
}

static void GymModificarNombre(char* nombreViejo, char* nombreNuevo, int size)
{
	printf("\nNombre actual: %s\n", nombreViejo);

	printf("Ingresar nuevo nombre (vacio para cancelar): ");
	ScannerString(nombreNuevo, size);

	snprintf(nombreNuevo, size, "%s", UtilidadesStringTrim(nombreNuevo));
}

static void GymModificarGenero(char* generoViejo, char* generoNuevo, int size)
{
	printf("\nGenero actual: %s\n", generoViejo);

	printf("Ingresar nuevo genero (vacio para cancelar): ");
	ScannerString(generoNuevo, size);

	snprintf(generoNuevo, size, "%s", UtilidadesStringTrim(generoNuevo));
}

static double GymModificarPrecio(double precioViejo)
{
	printf("\nPrecio actual: %.2f\n", precioViejo);

	printf("Ingresar nuevo precio (-1 para cancelar): ");
	double precio = ScannerDouble();

	return precio;
}

static Horario GymModificarHorario(Horario horarioViejo)
{
	Horario nuevo = { 0 };

	printf("\nHorario actual: %d:%d\n", horarioViejo.horas, horarioViejo.minutos);

	printf("Ingrese nueva hora de inicio: ");
	nuevo.horas = ScannerInt();

	printf("Ingrese minuto de inicio: ");
	nuevo.minutos = ScannerInt();

	return nuevo;
}

static Duracion GymModificarDuracion(Duracion duracionViejo)
{
	Duracion nuevo = { 0 };

	printf("\nDuracion actual: %d:%d\n", duracionViejo.horas, duracionViejo.minutos);

	printf("Ingrese horas de duracion: ");
	nuevo.horas = ScannerInt();

	printf("Ingrese minutos de duracion: ");
	nuevo.minutos = ScannerInt();

	return nuevo;
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