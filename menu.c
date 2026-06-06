#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "menu.h"
#include "cliente.h"
#include "entrenador.h"
#include "sector.h"
#include "clase.h"
#include "archivos.h"

void MenuSecundario(Gym* gym, char* nombreAccion, int accion);
void MenuSecundarioAccionCliente(Gym* gym, int accion);
void MenuSecundarioAccionEntrenador(Gym* gym,int accion);
void MenuSecundarioAccionSector(Gym* gym, int accion);
void MenuSecundarioAccionClase(Gym* gym, int accion);
void Pausa(void);

void MostrarMenu(Gym* gym)
{
	int opcion = 0;

	do
	{
		printf("\n----Sistema Gestion UtnGYM----\n");
		printf("\n");
		printf("Seleccione la accion a realizar\n");
		printf("\n1. Agregar \n");
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
			MenuSecundario(gym,"Buscar", opcion);
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
void MenuSecundario(Gym* gym, char* nombreAccion, int accion)
{
	int opcion = 0;

	do
	{

		printf("1. Cliente\n");
		printf("2. Entrenador\n");
		printf("3. Sector\n");
		printf("4. Clase\n\n");
		printf("0. Volver\n");
		printf("Elija la opcion: ");
		scanf_s("%d", &opcion);
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
void MenuSecundarioAccionCliente(Gym* gym, int accion)
{
	int id;

	switch (accion)
	{
	case 1: 
		gym->clientes = ClienteAgregarCliente(gym->clientes, &gym->clientesSize);
		break;
	case 2: 
		printf(" ingrese ID del cliente: \n");
		id = ScannerInt();
		ClienteModificarCliente(gym->clientes, gym->clientesSize, id);
		break;
	case 3:
		ClienteMostrarCliente(gym->clientes, gym->clientesSize);
		break;
	case 4:
		printf(" ingrese ID del cliente: \n");
		id = ScannerInt();
		if (ClienteBuscarClienteId(gym->clientes, gym->clientesSize, id, 0) != -1)
		{
			printf(" cliente encontrado. \n");
		}
		else
		{
			printf(" cliente no encontrado. \n");
		}
		break;
	case 5:
		printf(" ingrese ID del cliente: ");
		id = ScannerInt();
		gym->clientes = ClienteEliminarCliente(gym->clientes, &gym->clientesSize, id);
		break;
	case 6:
		//exportara txt
		break;

	}
}
void MenuSecundarioAccionEntrenador(Gym* gym, int accion)
{
	int id;

	switch (accion)
	{
	case 1: 
		gym->entrenadores = EntrenadorAgregarEntrenador(gym->entrenadores, &gym->entrenadoresSize);
		break;
	case 2:
		printf(" ingrese ID del entrenador: ");
		id = ScannerInt();
		EntrenadorModificarEntrenador(gym->entrenadores, gym->entrenadoresSize, id);
		break;
	case 3:
		EntrenadorMostrarEntrenadores(gym->entrenadores, gym->entrenadoresSize);
		break;
	case 4:
		printf(" ingrese ID del entrenador: ");
		id = ScannerInt();
		if (EntrenadorBuscarEntrenadorId(gym->entrenadores, gym->entrenadoresSize, id, 0) != -1)
		{
			printf(" entrenador encontrado. \n");
		} 
		else
		{
			printf(" entrenador no encontrado. \n");
		}
		break;
	case 5:
		printf(" ingrese ID del entrenador: \n");
		id = ScannerInt();
		gym->entrenadores = EntrenadorEliminarEntrenador(gym->entrenadores, &gym->entrenadoresSize, id);
		break;
	case 6:
		//exportara txt
		break;
	}
}
void MenuSecundarioAccionSector(Gym* gym, int accion)
{
	int id;
	switch (accion)
	{
	case 1: 
		gym->sectores = SectorAgregarSector(gym->sectores, &gym->sectoresSize);
		break;
	case 2: 
		printf(" ingrese ID del sector: ");
		id = ScannerInt();
		SectorModificarSector(gym->sectores, gym->sectoresSize,id);
		break;
	case 3:
		SectorMostrarSector(gym->sectores, gym->sectoresSize);
		break;
	case 4:
		printf(" ingrese ID del sector: ");
		id = ScannerInt();
		if (SectorBuscarSectorId(gym->sectores, gym->sectoresSize, id, 0) != -1)
		{
			printf(" sector encontrado. \n");
		}
		else
		{
			printf(" sector no encontrado. \n");
		}
		break;
	case 5:
		printf(" ingrese ID del sector: \n");
		id = ScannerInt();
		gym->sectores = SectorEliminarSector(gym->sectores, &gym->sectoresSize, id);
		break;
	case 6:
		//exportara txt
		break;
	}

}
void MenuSecundarioAccionClase(Gym* gym, int accion)
{
	int id;
	switch (accion)
	{
	case 1: 
		gym->clases = ClaseAgregarClase(gym->clases, &gym->clasesSize);
		break;
	case 2: 
		printf(" ingrese ID de la clase: ");
	id= ScannerInt();
		ClaseModificarClase(gym->clases, gym->clasesSize,id);
		break;
	case 3:
		ClaseMostrarClase(gym->clases, gym->clasesSize);
		break;
	case 4:
		printf(" ingrese ID de la clase: ");
		id = ScannerInt();
		if (ClaseBuscarClaseId(gym->clases, gym->clasesSize, id, 0) != -1)
		{
			printf(" clase encontrada. \n");
		}
		else
		{
			printf(" clase no encontrada. \n");
		}
		break;
	case 5:
		printf(" ingrese ID de la clase: ");
		id = ScannerInt();
		gym->clases = ClaseEliminarClase(gym->clases, &gym->clasesSize, id);
		break;
	case 6:
		//exportara txt
		break;
	}

}



void Pausa(void)
{
	printf("\npresione enter para continuar\n");
	system("pause");
}
