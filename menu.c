#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

void MenuSecundario(char* nombreAccion, int accion);
void MenuSecundarioAccionCliente(int accion);
void MenuSecundarioAccionEntrenador(int accion);
void MenuSecundarioAccionSector(int accion);
void MenuSecundarioAccionClase(int accion);
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
		printf("4. Eliminar\n");
		printf("5. Buscar\n");
		printf("6.Exportar a .txt\n\n");
		printf("0. Salir\n");

		printf("\nElija una opcion: ");
		scanf_s("%d", &opcion);
		switch (opcion)
		{
		case 1:
			MenuSecundario("Agregar", opcion);
			Pausa();
			break;

		case 2:
			MenuSecundario("Modificar", opcion);
			Pausa();
			break;
		case 3:
			MenuSecundario("Mostrar", opcion);
			Pausa();
			break;
		case 4:
			MenuSecundario("Eliminar", opcion);
			Pausa();
			break;
		case 5:
			MenuSecundario("Buscar", opcion);
			Pausa();
			break;

		case 6:
			MenuSecundario("Exportar", opcion);
			Pausa();
			break;
		}


	} while (opcion != 0);
}
void MenuSecundarioAccionCliente(int accion)
{
	switch (accion)
	{
	case 1: //agregar cliente
		break;
	case 2: // modificiar cliente
		break;
	case 3:
		//Mostrar cliente
		break;
	case 4:
		//buscar cliente
		break;
	case 5:
		//eliminar cliente
		break;
	case 6:
		//exportara txt
		break;

	}
}
void MenuSecundarioAccionEntrenador(int accion)
{
	switch (accion)
	{
	case 1: //agregar entrenador
		break;
	case 2: // modificiar entrenador
		break;
	case 3:
		//Mostrar entrenador
		break;
	case 4:
		//buscar entrenador
		break;
	case 5:
		//eliminar entrenador
		break;
	case 6:
		//exportara txt
		break;
	}
}
void MenuSecundarioAccionSector(int accion)
{
	switch (accion)
	{
	case 1: //agregar sector
		break;
	case 2: // modificiar sector
		break;
	case 3:
		//Mostrar sector
		break;
	case 4:
		//buscar sector
		break;
	case 5:
		//eliminar sector
		break;
	case 6:
		//exportara txt
		break;
	}

}
void MenuSecundarioAccionClase(int accion)
{
	switch (accion)
	{
	case 1: //agregar clase
		break;
	case 2: // modificiar clase
		break;
	case 3:
		//Mostrar clase
		break;
	case 4:
		//buscar clase
		break;
	case 5:
		//eliminar clase
		break;
	case 6:
		//exportara txt
		break;
	}

}



void MenuSecundario(char* nombreAccion, int accion)
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
			MenuSecundarioAccionCliente(accion);
			break;

		case 2:
			MenuSecundarioAccionEntrenador(accion);
			break;
		case 3:
			MenuSecundarioAccionSector(accion);
			break;
		case 4:
			MenuSecundarioAccionClase(accion);

			break;

		}

	} while (opcion != 0);
}
void Pausa(void)
{
	printf("\npresione enter para continuar\n");
	system("pause");
}
