#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constgym.h"
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

void GymCargarDatos(Gym* gym)
{
	ArchivoCargarGym(gym);

	if (gym->entrenadores != NULL)
	{
		EntrenadorOrdenarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
	}

	if (gym->sectores != NULL)
	{
		SectorOrdenarSectores(gym->sectores, gym->sectoresSize);
	}

	if(gym->clases != NULL)
	{
		ClaseOrdenarClases(gym->clases, gym->clasesSize);
	}

	if (gym->clientes != NULL)
	{
		ClienteOrdenarClientes(gym->clientes, gym->clientesSize);
	}

}

int GymAgregarEntrenador(Gym* gym, char* nombreEntrenador, char* generoEntrenador)
{
	Entrenador* temp = EntrenadorAgregarEntrenador(gym->entrenadores, gym->entrenadoresSize, gym->ids.entrenador + 1, nombreEntrenador, generoEntrenador);

	if (temp == NULL)
	{
		GymExit(gym);

		return ID_INVALIDO;
	}

	gym->entrenadores = temp;
	gym->entrenadoresSize++;
	gym->ids.entrenador++;

	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, gym->ids.entrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, gym->ids.entrenador) devolvio NULL");

		GymExit(gym);

		return ID_INVALIDO;
	}

	ArchivoAgregarEntrenador(entrenador);
	ArchivoActualizarIds(&gym->ids);

	return gym->ids.entrenador;
}

void GymModificarEntrenadorNombre(Gym* gym, int idEntrenador, char* nombreNuevo)
{
	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	EntrenadorModificarEntrenadorNombre(gym->entrenadores, gym->entrenadoresSize, idEntrenador, nombreNuevo);

	ArchivoModificarEntrenador(entrenador);
}

void GymModificarEntrenadorGenero(Gym* gym, int idEntrenador, char* generoNuevo)
{
	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	EntrenadorModificarEntrenadorGenero(gym->entrenadores, gym->entrenadoresSize, idEntrenador, generoNuevo);

	ArchivoModificarEntrenador(entrenador);
}

int GymObtenerEntrenadoresNombresIds(Gym* gym, char nombresEntrenadores[][MAX_NOMBRE_TEXT], int* idsEntrenadores)
{
	EntrenadorObtenerEntrenadoresNombresIds(gym->entrenadores, gym->entrenadoresSize, nombresEntrenadores, idsEntrenadores);

	return gym->entrenadoresSize;
}

void GymObtenerEntrenadorNombre(Gym* gym, int idEntrenador, char* nombreEntrenador)
{
	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	EntrenadorObtenerEntrenadorNombre(entrenador, nombreEntrenador);
}

void GymObtenerEntrenadorGenero(Gym* gym, int idEntrenador, char* generoEntrenador)
{
	Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador);

	if (entrenador == NULL)
	{
		printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idEntrenador) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	EntrenadorObtenerEntrenadorGenero(entrenador, generoEntrenador);
}

void GymEliminarEntrenador(Gym* gym, int idEntrenador)
{
	while (GymHayEntrenadorEnClases(gym, idEntrenador))
	{
		int index = ClaseBuscarClaseEntrenadorId(gym->clases, gym->clasesSize, idEntrenador);

		ClaseEliminarEntrenador(&gym->clases[index]);
	}
	
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
	int entrenadoresSize = gym->entrenadoresSize;
	int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
	char nombresEntrenadores[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };
	char generoEntrenadores[MAX_ARRAY_SIZE][MAX_GENERO_TEXT] = { 0 };

	EntrenadorObtenerEntrenadoresNombresIds(gym->entrenadores, gym->entrenadoresSize, nombresEntrenadores, idsEntrenadores);
	EntrenadorObtenerEntrenadoresGeneros(gym->entrenadores, gym->entrenadoresSize, generoEntrenadores);

	ArchivoExportarEntrenadores(entrenadoresSize, idsEntrenadores, nombresEntrenadores, generoEntrenadores);
}

int GymHayEntrenadores(Gym* gym)
{
	if (gym->entrenadores == NULL)
	{
		return 0;
	}

	return gym->entrenadoresSize;
}

int GymAgregarSector(Gym* gym, char* nombreSector)
{
	Sector* temp = SectorAgregarSector(gym->sectores, gym->sectoresSize, gym->ids.sector + 1, nombreSector);

	if (temp == NULL)
	{
		GymExit(gym);

		return ID_INVALIDO;
	}

	gym->sectores = temp;
	gym->sectoresSize++;
	gym->ids.sector++;

	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, gym->ids.sector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, gym->ids.sector)  devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	ArchivoAgregarSector(sector);
	ArchivoActualizarIds(&gym->ids);

	return gym->ids.sector;
}

void GymModificarSectorNombre(Gym* gym, int idSector, char* nombreNuevo)
{
	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector)  devolvio NULL\n");

		GymExit(gym);

		return;
	}

	SectorModificarSectorNombre(gym->sectores, gym->sectoresSize, idSector, nombreNuevo);

	ArchivoModificarSector(sector);
}

int GymObtenerSectoresNombresIds(Gym* gym, char nombresSectores[][MAX_NOMBRE_TEXT], int* idsSectores)
{
	SectorObtenerSectoresNombresIds(gym->sectores, gym->sectoresSize, nombresSectores, idsSectores);

	return gym->sectoresSize;
}

void GymObtenerSectorNombre(Gym* gym, int idSector, char* nombreSector)
{
	Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector);

	if (sector == NULL)
	{
		printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, idSector) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	SectorObtenerSectorNombre(sector, nombreSector);
}

void GymEliminarSector(Gym* gym, int idSector)
{
	while (GymHaySectorEnClases(gym, idSector))
	{
		int index = ClaseBuscarClaseSectorId(gym->clases, gym->clasesSize, idSector);

		ClaseEliminarSector(&gym->clases[index]);
	}
	
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
	int sectoresSize = gym->sectoresSize;
	int idsSectores[MAX_ARRAY_SIZE] = { 0 };
	char nombresSectores[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };

	SectorObtenerSectoresNombresIds(gym->sectores, gym->sectoresSize, nombresSectores, idsSectores);
	
	ArchivoExportarSectores(sectoresSize, idsSectores, nombresSectores);
}

int GymHaySectores(Gym* gym)
{
	if (gym->sectores == NULL)
	{
		return 0;
	}

	return gym->sectoresSize;
}

int GymAgregarClase(Gym* gym, char* nombreClase, int idEntrenador, int idSector, int horaHorario, int minutosHorario, int horaDuracion, int minutosDuracion, double precio)
{
	Horario inicio = { .horas = horaHorario, .minutos = minutosHorario };
	Duracion duracion = { .horas = horaDuracion, .minutos = minutosDuracion };	

	if (ClaseChequearClaseHorarioDuracion(gym->clases, gym->clasesSize, gym->ids.clase + 1, idEntrenador, idSector, inicio, duracion) == 1)
	{
		printf("[ERROR] El horario se superpone con otra clase\n");

		return ID_INVALIDO;
	}

	inicio.esValido = 1;
	duracion.esValido = 1;

	Clase* temp = ClaseAgregarClase(gym->clases, gym->clasesSize, gym->ids.clase + 1, nombreClase, idEntrenador, idSector, precio, inicio, duracion);

	if (temp == NULL)
	{
		GymExit(gym);

		return ID_INVALIDO;
	}

	gym->clases = temp;
	gym->clasesSize++;
	gym->ids.clase++;

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, gym->ids.clase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, gym->ids.clase)  devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	ArchivoAgregarClase(clase);
	ArchivoActualizarIds(&gym->ids);

	return gym->ids.clase;
}

void GymModificarClaseNombre(Gym* gym, int idClase, char* nombreNuevo)
{

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ClaseModificarClaseNombre(gym->clases, gym->clasesSize, idClase, nombreNuevo);
	ArchivoModificarClase(clase);
}

void GymAsignarClasePrecio(Gym* gym, int idClase, double precioNuevo)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ClaseAsignarPrecio(clase, precioNuevo);

	ArchivoModificarClase(clase);
}

int GymModificarClaseHorario(Gym* gym, int idClase, int horasHorario, int minutosHorario)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	Horario horarioNuevo = { .horas = horasHorario, .minutos = minutosHorario };
	Duracion duracionActual = ClaseObtenerClaseDuracion(clase);
	int idEntrenador = ClaseObtenerEntrenador(clase);
	int idSector = ClaseObtenerSector(clase);

	if (ClaseChequearClaseHorarioDuracion(gym->clases, gym->clasesSize, idClase, idEntrenador, idSector, horarioNuevo, duracionActual) == 1)
	{
		printf("[ERROR] El horario se superpone con otra clase\n");

		return ID_INVALIDO;
	}

	horarioNuevo.esValido = 1;

	ClaseModificarClaseHorario(clase, horarioNuevo);

	ArchivoModificarClase(clase);

	return idClase;
}

int GymModificarClaseDuracion(Gym* gym, int idClase, int horasDuracion, int minutosDuracion)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	Horario horarioActual = ClaseObtenerClaseHorario(clase);
	Duracion duracionNuevo = { .horas = horasDuracion, .minutos = minutosDuracion };
	int idEntrenador = ClaseObtenerEntrenador(clase);
	int idSector = ClaseObtenerSector(clase);

	if (ClaseChequearClaseHorarioDuracion(gym->clases, gym->clasesSize, idClase, idEntrenador, idSector, horarioActual, duracionNuevo) == 1)
	{
		printf("[ERROR] El horario se superpone con otra clase\n");

		return ID_INVALIDO;
	}

	duracionNuevo.esValido = 1;

	ClaseModificarClaseDuracion(clase, duracionNuevo);

	ArchivoModificarClase(clase);

	return idClase;
}

int GymObtenerClasesDelDia(Gym* gym, int idSector, char nombresClases[][MAX_NOMBRE_TEXT], int* idsClases)
{

	return 1;
}

int GymObtenerClasesNombresIds(Gym* gym, char nombresClases[][MAX_NOMBRE_TEXT], int* idsClases)
{
	ClaseObtenerClasesNombresIds(gym->clases, gym->clasesSize, nombresClases, idsClases);

	return gym->clasesSize;
}

int GymObtenerClaseClientesNombresIds(Gym* gym, int idClase, char nombresClientes[MAX_IDS][MAX_NOMBRE_TEXT], int* idsClientes)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	int idsSize = ClaseObtenerCantidadClientesEnClase(clase);

	ClaseObtenerClaseClientesIds(clase, idsClientes);

	for (int i = 0; i < idsSize; i++)
	{
		Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idsClientes[i]);

		if (cliente == NULL)
		{
			printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL\n");

			GymExit(gym);

			return ID_INVALIDO;
		}

		snprintf(nombresClientes[i], MAX_NOMBRE_TEXT, "%s", cliente->nombre);
	}

	return idsSize;
}

void GymObtenerClaseNombre(Gym* gym, int idClase, char* nombreViejo)
{
	ClaseObtenerClaseNombre(gym->clases, gym->clasesSize, idClase, nombreViejo);
}

double GymObtenerClasePrecio(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return 0;
	}

	return ClaseObtenerClasePrecio(clase);
}

void GymObtenerClaseHorario(Gym* gym, int idClase, int* horas, int* minutos)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}
	
	Horario horario = ClaseObtenerClaseHorario(clase);

	*horas = horario.horas;
	*minutos = horario.minutos;
}

void GymObtenerClaseDuracion(Gym* gym, int idClase, int* horas, int* minutos)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	Duracion duracion= ClaseObtenerClaseDuracion(clase);

	*horas = duracion.horas;
	*minutos = duracion.minutos;
}

int GymObtenerClaseEntrenadorId(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	return ClaseObtenerEntrenador(clase);
}

int GymObtenerClaseSectorId(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idClase) devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	return ClaseObtenerSector(clase);
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

		int idsClientes[MAX_IDS] = { 0 };

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
	int clasesSize = gym->clasesSize;
	int clientesSize = gym->clientesSize;
	int idsClases[MAX_ARRAY_SIZE] = { 0 };
	char nombresClases[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };
	int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
	char nombresEntrenadores[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };
	int idsSectores[MAX_ARRAY_SIZE] = { 0 };
	char nombresSectores[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };
	int idsClasesClientes[MAX_ARRAY_SIZE][MAX_IDS] = { 0 };
	int idsClientes[MAX_ARRAY_SIZE] = { 0 };
	char nombresClientes[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };
	int clasesClientesValidos[MAX_ARRAY_SIZE] = { 0 };
	double preciosClases[MAX_ARRAY_SIZE] = { 0 };
	int inicioHorasClases[MAX_ARRAY_SIZE] = { 0 };
	int inicioMinutosClases[MAX_ARRAY_SIZE] = { 0 };
	int duracionHorasClases[MAX_ARRAY_SIZE] = { 0 };
	int duracionMinutosClases[MAX_ARRAY_SIZE] = { 0 };

	ClaseObtenerClasesIds(gym->clases, gym->clasesSize, idsClases);
	ClaseObtenerClasesNombres(gym->clases, gym->clasesSize, nombresClases);
	ClaseObtenerClasesEntrenadores(gym->clases, gym->clasesSize, idsEntrenadores);
	ClaseObtenerClasesSectores(gym->clases, gym->clasesSize, idsSectores);
	ClaseObtenerClasesClientes(gym->clases, gym->clasesSize, idsClasesClientes, clasesClientesValidos);
	ClaseObtenerClasesPrecios(gym->clases, gym->clasesSize, preciosClases);
	ClaseObtenerClasesHorarios(gym->clases, gym->clasesSize, inicioHorasClases, inicioMinutosClases);
	ClaseObtenerClasesDuracion(gym->clases, gym->clasesSize, duracionHorasClases, duracionMinutosClases);

	for (int i = 0; i < clasesSize; i++)
	{
		Entrenador* entrenador = EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idsEntrenadores[i]);

		if (entrenador == NULL)
		{
			printf("[ERROR] EntrenadorObtenerEntrenador(gym->entrenadores, gym->entrenadoresSize, idsEntrenadores[i]) devolvio NULL\n");

			GymExit(gym);

			return;
		}
		
		EntrenadorObtenerEntrenadorNombre(entrenador, nombresEntrenadores[i]);
	}

	for (int i = 0; i < clasesSize; i++)
	{
		Sector* sector = SectorObtenerSector(gym->sectores, gym->sectoresSize, idsSectores[i]);

		if (sector == NULL)
		{
			printf("[ERROR] SectorObtenerSector(gym->sectores, gym->sectoresSize, idsSectores[i]) devolvio NULL\n");

			GymExit(gym);

			return;
		}

		SectorObtenerSectorNombre(sector, nombresSectores[i]);
	}

	ClienteObtenerClientesNombresIds(gym->clientes, gym->clientesSize, nombresClientes, idsClientes);

	ArchivoExportarClases(clasesSize, idsClases, nombresClases, nombresEntrenadores, nombresSectores, idsClasesClientes, clientesSize, idsClientes, nombresClientes, 
							clasesClientesValidos, preciosClases, inicioHorasClases, inicioMinutosClases, duracionHorasClases, duracionMinutosClases);
}

int GymHayClientesEnClase(Gym* gym, int idClase)
{
	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase %d\n", idClase);

		GymExit(gym);

		return 0;
	}

	return ClaseObtenerCantidadClientesEnClase(clase);
}

int GymHayEntrenadorEnClases(Gym* gym, int idEntrenador)
{
	return (ClaseBuscarClaseEntrenadorId(gym->clases, gym->clasesSize, idEntrenador) == ID_INVALIDO) == 0;
}

int GymHaySectorEnClases(Gym* gym, int idSector)
{
	return (ClaseBuscarClaseSectorId(gym->clases, gym->clasesSize, idSector) == ID_INVALIDO) == 0;
}

int GymHayClases(Gym* gym)
{
	if (gym->clases == NULL)
	{
		return 0;
	}

	return gym->clasesSize;
}

int GymAgregarCliente(Gym* gym, char* nombreCliente, char* generoCliente)
{
	Cliente* temp = ClienteAgregarCliente(gym->clientes, gym->clientesSize, gym->ids.cliente + 1, nombreCliente, generoCliente);

	if (temp == NULL)
	{
		GymExit(gym);

		return ID_INVALIDO;
	}

	gym->clientes = temp;
	gym->clientesSize++;
	gym->ids.cliente++;

	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, gym->ids.cliente);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, gym->ids.cliente) devolvio NULL\n");

		GymExit(gym);

		return ID_INVALIDO;
	}

	ArchivoAgregarCliente(cliente);
	ArchivoActualizarIds(&gym->ids);

	return gym->ids.cliente;
}

void GymModificarClienteNombre(Gym* gym, int idCliente, char* nombreNuevo)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ClienteModificarClienteNombre(gym->clientes, gym->clientesSize, idCliente, nombreNuevo);

	ArchivoModificarCliente(cliente);
}

void GymModificarClienteGenero(Gym* gym, int id, char* generoNuevo )
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, id);

	if (cliente == NULL)
	{
		printf("[ERROR] ClienteObtenerCliente(gym->clientes, gym->clientesSize, id) devolvio NULL\n");

		GymExit(gym);

		return;
	}

	ClienteModificarClienteGenero(gym->clientes, gym->clientesSize, id, generoNuevo);

	ArchivoModificarCliente(cliente);
}

int GymObtenerClientesNombresIds(Gym* gym, char nombresClientes[][MAX_NOMBRE_TEXT], int* idsClientes)
{
	ClienteObtenerClientesNombresIds(gym->clientes, gym->clientesSize, nombresClientes, idsClientes);

	return gym->clientesSize;
}

int GymObtenerClienteClasesNombresIds(Gym* gym, int idCliente, char nombresClases[MAX_IDS][MAX_NOMBRE_TEXT], int* idsClases)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return 0;
	}

	int idsSize = ClienteObtenerCantidadClasesEnCliente(cliente);

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

		snprintf(nombresClases[i], MAX_NOMBRE_TEXT, "%s", clase->nombre);
	}

	return idsSize;
}

void GymObtenerClienteNombre(Gym* gym, int idCliente, char* nombreCliente)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return;
	}

	ClienteObtenerClienteNombre(cliente, nombreCliente);
}

void GymObtenerClienteGenero(Gym* gym, int idCliente, char* generoCliente)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return;
	}

	ClienteObtenerClienteGenero(cliente, generoCliente);
}

void GymObtenerClientesMontoTotalClases(Gym* gym, int size, int* idsClientes, double* montoTotalClases)
{
	for (int i = 0; i < size; i++)
	{
		montoTotalClases[i] = GymObtenerClienteMontoTotalClases(gym, idsClientes[i]);
	}
}

double GymObtenerClienteMontoTotalClases(Gym* gym, int idCliente)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return 0;
	}

	int clienteClasesSize = 0;
	int idsClienteClases[MAX_IDS] = { 0 };
	double montoTotalClases = 0.0;

	clienteClasesSize = ClienteObtenerCantidadClasesEnCliente(cliente);
	ClienteObtenerClienteClasesIds(cliente, idsClienteClases);

	for (int i = 0; i < clienteClasesSize; i++)
	{
		Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idsClienteClases[i]);

		if (clase == NULL)
		{
			printf("[ERROR] ClaseObtenerClase(gym->clases, gym->clasesSize, idsClienteClases[i]) devolvio NULL\n");

			GymExit(gym);

			return 0;
		}

		montoTotalClases += ClaseObtenerClasePrecio(clase);
	}

	return montoTotalClases;
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

		int idsClases[MAX_IDS] = { 0 };

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

int GymAgregarClienteClase(Gym* gym, int idCliente, int idClase)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return 0;
	}

	Clase* clase = ClaseObtenerClase(gym->clases, gym->clasesSize, idClase);

	if (clase == NULL)
	{
		printf("[ERROR] No se encontro la clase %d\n", idClase);

		GymExit(gym);

		return 0;
	}

	int exito = ClienteAgregarClase(cliente, idClase);

	if (exito == 0)
	{
		return 0;
	}

	exito = ClaseAgregarCliente(clase, idCliente);

	if (exito == 0)
	{
		return 0;
	}

	ArchivoModificarCliente(cliente);
	ArchivoModificarClase(clase);

	return 1;
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
	int clientesSize = gym->clientesSize;
	int clasesSize = gym->clasesSize;
	int idsClientes[MAX_ARRAY_SIZE] = { 0 };
	char nombresClientes[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };
	char generosClientes[MAX_ARRAY_SIZE][MAX_GENERO_TEXT] = { 0 };
	int idsClientesClases[MAX_ARRAY_SIZE][MAX_IDS] = { 0 };
	int clientesClasesValidos[MAX_ARRAY_SIZE] = { 0 };
	double montosTotalClases[MAX_ARRAY_SIZE] = { 0 };
	int idsClases[MAX_ARRAY_SIZE] = { 0 };
	char nombresClases[MAX_ARRAY_SIZE][MAX_NOMBRE_TEXT] = { 0 };

	ClienteObtenerClientesIds(gym->clientes, gym->clientesSize, idsClientes);
	ClienteObtenerClientesNombres(gym->clientes, gym->clientesSize, nombresClientes);
	ClienteObtenerClientesGeneros(gym->clientes, gym->clientesSize, generosClientes);
	ClienteObtenerClientesClases(gym->clientes, gym->clientesSize, idsClientesClases, clientesClasesValidos);
	
	GymObtenerClientesMontoTotalClases(gym, gym->clientesSize, idsClientes, montosTotalClases);

	ClaseObtenerClasesNombresIds(gym->clases, gym->clasesSize, nombresClases, idsClases);

	ArchivoExportarClientes(clientesSize, idsClientes, nombresClientes, generosClientes, idsClientesClases, clientesClasesValidos, montosTotalClases, 
		clasesSize, idsClases, nombresClases);
}

int GymHayClasesEnCliente(Gym* gym, int idCliente)
{
	Cliente* cliente = ClienteObtenerCliente(gym->clientes, gym->clientesSize, idCliente);

	if (cliente == NULL)
	{
		printf("[ERROR] No se encontro el cliente %d\n", idCliente);

		GymExit(gym);

		return 0;
	}
	
	return ClienteObtenerCantidadClasesEnCliente(cliente);
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