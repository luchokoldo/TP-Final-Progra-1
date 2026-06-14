#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "menu.h"
#include "cliente.h"
#include "entrenador.h"
#include "sector.h"
#include "clase.h"
#include "archivos.h"

#define MAX_MENU_ITEMS  7

#define MENU_PREV       8
#define MENU_NEXT       9
#define MENU_EXIT       0

#define MENU_EXIT_VALUE -1

static void MenuSecundario(Gym* gym, char* nombreAccion, int accion);
static void MenuSecundarioAccionCliente(Gym* gym, int accion);
static void MenuSecundarioAccionEntrenador(Gym* gym, int accion);
static void MenuSecundarioAccionSector(Gym* gym, int accion);
static void MenuSecundarioAccionClase(Gym* gym, int accion);
static void Pausa(void);

void MenuMostrarMenu(Gym* gym)
{
	int opcion = 0;

	do
	{
		printf("\n----Sistema Gestion UtnGYM----\n\n");
		printf("\n");
		printf("Seleccione la accion a realizar\n\n");
		printf("1. Agregar\n");
		printf("2. Modificar\n");
		printf("3. Mostrar\n");
		printf("4. Buscar\n");
		printf("5. Eliminar\n");
		printf("6. Exportar a .txt\n\n");
		printf("0. Salir\n");

		printf("\nElija una opcion: ");
		opcion = ScannerInt();
		switch (opcion)
		{
		case 1:
			MenuSecundario(gym, "Agregar", opcion);
			Pausa();
			break;

		case 2:
			MenuSecundario(gym, "Modificar", opcion);
			Pausa();
			break;
		case 3:
			MenuSecundario(gym, "Mostrar", opcion);
			Pausa();
			break;
		case 4:
			MenuSecundario(gym, "Buscar", opcion);
			Pausa();
			break;
		case 5:
			MenuSecundario(gym, "Eliminar", opcion);
			Pausa();
			break;

		case 6:
			MenuSecundario(gym, "Exportar", opcion);
			Pausa();
			break;
		}


	} while (opcion != 0);
}
static void MenuSecundario(Gym* gym, char* nombreAccion, int accion)
{
	int opcion = 0;

	do
	{
		printf("\t%s\n\n", nombreAccion);
		printf("1. Cliente\n");
		printf("2. Entrenador\n");
		printf("3. Sector\n");
		printf("4. Clase\n\n");
		printf("0. Volver\n");
		printf("Elija la opcion: ");
		opcion = ScannerInt();
		switch (opcion)
		{

		case 1:
			MenuSecundarioAccionCliente(gym, accion);
			break;
		case 2:
			MenuSecundarioAccionEntrenador(gym, accion);
			break;
		case 3:
			MenuSecundarioAccionSector(gym, accion);
			break;
		case 4:
			MenuSecundarioAccionClase(gym, accion);
			break;

		}

	} while (opcion != 0);
}
static void MenuSecundarioAccionCliente(Gym* gym, int accion)
{
	int id;
	int indice;
	switch (accion)
	{
	case 1: 
		gym->clientes = ClienteAgregarCliente(gym->clientes, &gym->clientesSize);
		if (gym->clientesSize > 0)
		{
		ArchivoAgregarCliente(&gym->clientes[gym->clientesSize - 1]);
		}
		break;
	case 2: 
		printf("Ingrese ID del cliente: ");
		id = ScannerInt();
		ClienteModificarCliente(gym->clientes, gym->clientesSize, id);
		indice = ClienteBuscarClienteId(gym->clientes, gym->clientesSize, id, 0);
		if (indice != -1)
		{
			ArchivoModificarCliente(&gym->clientes[indice]);
		}
		break;
	case 3:
		ClienteMostrarCliente(gym->clientes, gym->clientesSize);
		break;
	case 4:
		printf("Ingrese ID del cliente: ");
		id = ScannerInt();
		if (ClienteBuscarClienteId(gym->clientes, gym->clientesSize, id, 0) != -1)
		{
			printf("Cliente encontrado.\n");
		}
		else
		{
			printf("Cliente no encontrado.\n");
		}
		break;
	case 5:
		printf("Ingrese ID del cliente: ");
		id = ScannerInt();
		indice = ClienteBuscarClienteId(gym->clientes, gym->clientesSize, id, 0);
		if (indice != -1)
		{
			ArchivoBorrarCliente(&gym->clientes[indice]);
			printf("Cliente eliminado.\n");
		}
		else
		{
			printf("Cliente no encontrado.\n");
		}
		break;
	case 6:
		ArchivoExportarClientes(gym->clientes, gym->clientesSize);
		break;

	}
}
static void MenuSecundarioAccionEntrenador(Gym* gym, int accion)
{
	int id;
	int indice;
	switch (accion)
	{
	case 1: 
		gym->entrenadores = EntrenadorAgregarEntrenador(gym->entrenadores, &gym->entrenadoresSize);
		if (gym->entrenadoresSize > 0)
		{
			ArchivoAgregarEntrenador(&gym->entrenadores[gym->entrenadoresSize - 1]);
		}
		break;
	case 2:
		printf("Ingrese ID del entrenador: ");
		id = ScannerInt();
		EntrenadorModificarEntrenador(gym->entrenadores, gym->entrenadoresSize, id);
		indice = EntrenadorBuscarEntrenadorId(gym->entrenadores, gym->entrenadoresSize, id, 0);
		if (indice != -1)
		{
			ArchivoModificarEntrenador(&gym->entrenadores[indice]);
		}
		break;
	case 3:
		EntrenadorMostrarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
		break;
	case 4:
		printf("Ingrese ID del entrenador: ");
		id = ScannerInt();
		if (EntrenadorBuscarEntrenadorId(gym->entrenadores, gym->entrenadoresSize, id, 0) != -1)
		{
			printf("Entrenador encontrado.\n");
		} 
		else
		{
			printf("Entrenador no encontrado.\n");
		}
		break;
	case 5:
		printf("Ingrese ID del entrenador: ");
		id = ScannerInt();
		indice = EntrenadorBuscarEntrenadorId(gym->entrenadores, gym->entrenadoresSize, id, 0);
		if (indice != -1)
		{
			ArchivoBorrarEntrenador(&gym->entrenadores[indice]);
			printf("Entrenador eliminado.\n");
		}
		else
		{
			printf("Entrenador no encontrado.\n");
		}
		break;
	case 6:
		ArchivoExportarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
		break;
	}
}
static void MenuSecundarioAccionSector(Gym* gym, int accion)
{
	int id;
	int indice;
	switch (accion)
	{
	case 1: 
		gym->sectores = SectorAgregarSector(gym->sectores, &gym->sectoresSize);
		if (gym->sectoresSize > 0)
		{
			ArchivoAgregarSector(&gym->sectores[gym->sectoresSize - 1]);
		}
		break;
	case 2: 
		printf("Ingrese ID del sector: ");
		id = ScannerInt();
		SectorModificarSector(gym->sectores, gym->sectoresSize, id);
		indice = SectorBuscarSectorId(gym->sectores, gym->sectoresSize, id, 0);
		if (indice != -1)
		{
			ArchivoModificarSector(&gym->sectores[indice]);
		}
		break;
	case 3:
		SectorMostrarSector(gym->sectores, gym->sectoresSize);
		break;
	case 4:
		printf("Ingrese ID del sector: ");
		id = ScannerInt();
		if (SectorBuscarSectorId(gym->sectores, gym->sectoresSize, id, 0) != -1)
		{
			printf("Sector encontrado.\n");
		}
		else
		{
			printf("Sector no encontrado.\n");
		}
		break;
	case 5:
		printf("Ingrese ID del sector: ");
		id = ScannerInt();
		indice = SectorBuscarSectorId(gym->sectores, gym->sectoresSize, id, 0);
		if (indice != -1)
		{
			ArchivoBorrarSector(&gym->sectores[indice]);
			printf("Sector eliminado.\n");
		}
		else
		{
			printf("Sector no encontrado.\n");
		}
		break;
	case 6:
		ArchivoExportarSectores(gym->sectores, gym->sectoresSize);
		break;
	}

}
static void MenuSecundarioAccionClase(Gym* gym, int accion)
{
	int id;
	int indice;
	switch (accion)
	{
	case 1: 
		gym->clases = ClaseAgregarClase(gym->clases, &gym->clasesSize);
		if (gym->clasesSize > 0)
		{
			ArchivoAgregarClase(&gym->clases[gym->clasesSize - 1]);
		}
		break;
	case 2: 
		printf("Ingrese ID de la clase: ");
	    id = ScannerInt();
		ClaseModificarClase(gym->clases, gym->clasesSize, id);
		indice = ClaseBuscarClaseId(gym->clases, gym->clasesSize, id, 0);
		if (indice != -1)
		{
			ArchivoModificarClase(&gym->clases[indice]);
		}
		break;
	case 3:
		ClaseMostrarClase(gym->clases, gym->clasesSize);
		break;
	case 4:
		printf("Ingrese ID de la clase: ");
		id = ScannerInt();
		if (ClaseBuscarClaseId(gym->clases, gym->clasesSize, id, 0) != -1)
		{
			printf("Clase encontrada.\n");
		}
		else
		{
			printf("Clase no encontrada.\n");
		}
		break;
	case 5:
		printf("Ingrese ID de la clase: ");
		id = ScannerInt();
		indice = ClaseBuscarClaseId(gym->clases, gym->clasesSize, id, 0);
		if (indice != -1)
		{
			ArchivoBorrarClase(&gym->clases[indice]);
			printf("Clase eliminada.\n");
		}
		else
		{
			printf("Clase no encontrada.\n");
		}
		break;
	case 6:
		ArchivoExportarClases(gym->clases, gym->clasesSize);
		break;
	}

}

static void MenuListaAgregarVolver(int pagina)
{
	if (pagina > 1)
	{
		printf("%d. Volver\n", MENU_PREV);
	}
	else
	{
		printf("\n");
	}
}

static void MenuListaAgregarSiguiente(int size, int pagina)
{
	if (size > MAX_MENU_ITEMS * pagina)
	{
		printf("%d. Siguiente\n", MENU_NEXT);
	}
	else
	{
		printf("\n");
	}
}

static void MenuListaAgregarSalir(void)
{
	printf("\n%d. Salir\n\n", MENU_EXIT);
}

static int MenuListaObtenerOpcionValida(int size, int pagina)
{
	char opcion;
	int iOpcion;

	printf("Elegir opcion: ");

	opcion = ScannerChar();

	iOpcion = opcion - '0';

	if (iOpcion >= 0 && iOpcion <= 9)
	{
		int opcionesEnPagina = (size - MAX_MENU_ITEMS * (pagina - 1) < MAX_MENU_ITEMS) ?
			(size - MAX_MENU_ITEMS * (pagina - 1)) : MAX_MENU_ITEMS;

		if (iOpcion <= opcionesEnPagina ||
			(pagina > 1 && iOpcion == MENU_PREV) ||
			(size > MAX_MENU_ITEMS * pagina && iOpcion == MENU_NEXT))
		{
			return iOpcion;
		}
	}

	printf("[MENU] Opcion incorrecta. Intente de nuevo.\n");

	return MenuListaObtenerOpcionValida(size, pagina);
}

static int MenuListaCrearMenu(const char* titulo, char texto[][64], int textoSize, int pagina)
{
	printf("\n\t%s (Pagina %d)\n\n", titulo, pagina);

	int inicio = MAX_MENU_ITEMS * (pagina - 1);
	int fin = inicio + MAX_MENU_ITEMS;

	if (fin > textoSize)
	{
		fin = textoSize;
	}

	for (int i = inicio; i < fin; i++)
	{
		printf("%d. %s\n", (i % MAX_MENU_ITEMS) + 1, texto[i]);
	}

	printf("\n");

	MenuListaAgregarVolver(pagina);
	MenuListaAgregarSiguiente(textoSize, pagina);
	MenuListaAgregarSalir();

	int opcion = MenuListaObtenerOpcionValida(textoSize, pagina);

	switch (opcion)
	{
	case MENU_PREV:  return MenuListaCrearMenu(titulo, texto, textoSize, pagina - 1);
	case MENU_NEXT:  return MenuListaCrearMenu(titulo, texto, textoSize, pagina + 1);
	case MENU_EXIT:  return MENU_EXIT_VALUE;
	}

	return inicio + opcion - 1;
}

static void Pausa(void)
{
	printf("\nPresione enter para continuar\n");
	system("pause");
}
