#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "scanner.h"
#include "utilidades.h"

#define MAX_MENU_ARRAY_SIZE	256
#define MAX_MENU_TEXT_SIZE	64
#define MAX_MENU_ITEMS		7

#define MENU_PREV			8
#define MENU_NEXT			9
#define MENU_EXIT			0

#define MENU_EXIT_VALUE		-1

static int MenuMostrarMenuSecundario(Gym* gym, char* nombreAccion, int accion);
static void MenuSecundarioAccionCliente(Gym* gym, char* textoAccion, int accion);
static void MenuSecundarioAccionEntrenador(Gym* gym, char* textoAccion, int accion);
static void MenuSecundarioAccionSector(Gym* gym, char* textoAccion, int accion);
static void MenuSecundarioAccionClase(Gym* gym, char* textoAccion, int accion);
static int MenuListaCrearMenu(const char* titulo, char texto[][64], int textoSize, int pagina);
static int MenuListaObtenerOpcionValida(int size, int pagina);
static void MenuListaAgregarVolver(int pagina);
static void MenuListaAgregarSiguiente(int size, int pagina);
static void MenuListaAgregarSalir(void);
static void MenuPausa(void);
static int MenuListaClientes(Gym* gym, char* titulo, int* idsClientes);
static int MenuListaClases(Gym* gym, char* titulo, int* idsClases);
static int MenuListaSectores(Gym* gym, char* titulo, int* idsSectores);

void MenuMostrarMenu(Gym* gym)
{
	int opcion = MENU_EXIT_VALUE;

	char texto[][MAX_MENU_TEXT_SIZE] =
	{
		"Clientes",
		"Entrenadores",
		"Sectores",
		"Clases"
	};

	do
	{
		system("cls");

		opcion = MenuListaCrearMenu("Sistema de Gestion", texto, GET_CHARSMAX(texto), 1);

		if (opcion != MENU_EXIT_VALUE)
		{
			int opcionSecundario = MenuMostrarMenuSecundario(gym, texto[opcion], opcion);

			if (opcionSecundario != MENU_EXIT_VALUE)
			{
				MenuPausa();
			}
		}
	} while (opcion != MENU_EXIT_VALUE);
}

static int MenuMostrarMenuSecundario(Gym* gym, char* textoAccion, int accion)
{
	int opcion = MENU_EXIT_VALUE;

	char texto[][MAX_MENU_TEXT_SIZE] =
	{
		"Agregar",
		"Modificar",
		"Mostrar",
		"Buscar",
		"Eliminar",
		"Exportar a .txt"
	};

	opcion = MenuListaCrearMenu(textoAccion, texto, GET_CHARSMAX(texto), 1);

	switch (accion)
	{
		case 0:
			MenuSecundarioAccionCliente(gym, texto[opcion], opcion);
			break;
		case 1:
			MenuSecundarioAccionEntrenador(gym, texto[opcion], opcion);
			break;
		case 2:
			MenuSecundarioAccionSector(gym, texto[opcion], opcion);
			break;
		case 3:
			MenuSecundarioAccionClase(gym, texto[opcion], opcion);
			break;
	}

	return opcion;
}

static void MenuSecundarioAccionCliente(Gym* gym, char* accionTexto, int accion)
{
	switch (accion)
	{
		case 0: 
		{
			GymAgregarCliente(gym);

			break;
		}
		case 1: 
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			int idsClientes[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionClientes = MENU_EXIT_VALUE;

			opcionClientes = MenuListaClientes(gym, accionTexto, idsClientes);

			if (opcionClientes == MENU_EXIT_VALUE)
			{
				return;
			}

			char textoModificar[][MAX_MENU_TEXT_SIZE] =
			{
				"Nombre",
				"Genero",
				"Clases"
			};

			int opcionModificar = MenuListaCrearMenu(accionTexto, textoModificar, GET_CHARSMAX(textoModificar), 1);

			if (opcionModificar == MENU_EXIT_VALUE)
			{
				return;
			}

			switch (opcionModificar)
			{
				case 0: 
					GymModificarClienteNombre(gym, idsClientes[opcionClientes]);
					break;
				case 1:
					GymModificarClienteGenero(gym, idsClientes[opcionClientes]);
					break;
				case 2:
				{
					if (GymHayClases(gym) == 0)
					{
						printf("[ERROR] No hay Clases\n");

						return;
					}
			
					char textoClases[][MAX_MENU_TEXT_SIZE] =
					{
						"Agregar",
						"Eliminar"
					};

					char titulo[MAX_MENU_TEXT_SIZE];

					snprintf(titulo, MAX_MENU_TEXT_SIZE, "%s %s", accionTexto, textoModificar[opcionModificar]);

					int opcionClases = MenuListaCrearMenu(titulo, textoClases, GET_CHARSMAX(textoClases), 1);

					if (opcionClases == MENU_EXIT_VALUE)
					{
						return;
					}

					switch (opcionClases)
					{
						case 0:
						{
							int idsClases[MAX_MENU_ARRAY_SIZE] = { 0 };
							int opcionClases = MENU_EXIT_VALUE;

							opcionClases = MenuListaClases(gym, "Clases", idsClases);

							if (opcionClases == MENU_EXIT_VALUE)
							{
								return;
							}

							GymAgregarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							break;
						}
						case 1:
						{
							if (GymHayClasesEnCliente(gym, idsClientes[opcionClientes]) == 0)
							{
								printf("[ERROR] El cliente no tiene ninguna clase asignada.\n");

								return;
							}

							char nombresClases[MAX_ID_CLIENTE_SIZE][MAX_NOMBRE_CLIENTE_SIZE];
							int idsClases[MAX_ID_CLIENTE_SIZE] = { 0 };
							int clasesSize = 0;
							int opcionClases = MENU_EXIT_VALUE;
				
							clasesSize = GymObtenerClienteClasesNombresIds(gym, idsClientes[opcionClientes], nombresClases, idsClases);

							opcionClases = MenuListaCrearMenu("Clases", nombresClases, clasesSize, 1);

							if (opcionClases == MENU_EXIT_VALUE)
							{
								return;
							}

							GymEliminarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							break;
						}
					}

					break;
				}
			}
			
			break;
		}
		case 2:
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			GymMostrarClientes(gym);

			break;
		}
		case 3:
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			int idsClientes[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionClientes = MENU_EXIT_VALUE;

			opcionClientes = MenuListaClientes(gym, accionTexto, idsClientes);

			if (opcionClientes == MENU_EXIT_VALUE)
			{
				return;
			}

			GymMostrarCliente(gym, idsClientes[opcionClientes]);

			break;
		}
		case 4:
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			int idsClientes[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionClientes = MENU_EXIT_VALUE;

			opcionClientes = MenuListaClientes(gym, accionTexto, idsClientes);

			if (opcionClientes == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarCliente(gym, idsClientes[opcionClientes]);

			break;
		}
		case 5:
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			GymExportarClientesArchivoTexto(gym);

			break;
		}
	}
}

static void MenuSecundarioAccionEntrenador(Gym* gym, char* accionTexto, int accion)
{
	switch (accion)
	{
		case 0:
		{
			GymAgregarEntrenador(gym);

			break;
		}
		case 1:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			int idsEntrenadores[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionEntrenadores = MENU_EXIT_VALUE;

			opcionEntrenadores = MenuListaEntrenadores(gym, accionTexto, idsEntrenadores);

			if (opcionEntrenadores == MENU_EXIT_VALUE)
			{
				return;
			}

			char textoModificar[][MAX_MENU_TEXT_SIZE] =
			{
				"Nombre",
				"Genero"
			};

			int opcionModificar = MenuListaCrearMenu(accionTexto, textoModificar, GET_CHARSMAX(textoModificar), 1);

			if (opcionModificar == MENU_EXIT_VALUE)
			{
				return;
			}

			switch (opcionModificar)
			{
				case 0:
					GymModificarEntrenadorNombre(gym, idsEntrenadores[opcionEntrenadores]);
					break;
				case 1:
					GymModificarEntrenadorGenero(gym, idsEntrenadores[opcionEntrenadores]);
					break;
			}

			break;
		}
		case 2:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			GymMostrarEntrenadores(gym);

			break;
		}
		case 3:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			int idsEntrenadores[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionEntrenadores = MENU_EXIT_VALUE;

			opcionEntrenadores = MenuListaEntrenadores(gym, accionTexto, idsEntrenadores);

			if (opcionEntrenadores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymMostrarEntrenador(gym, idsEntrenadores[opcionEntrenadores]);

			break;
		}
		case 4:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			int idsEntrenadores[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionEntrenadores = MENU_EXIT_VALUE;

			opcionEntrenadores = MenuListaEntrenadores(gym, accionTexto, idsEntrenadores);

			if (opcionEntrenadores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarEntrenador(gym, idsEntrenadores[opcionEntrenadores]);

			break;
		}
		case 5:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			GymExportarEntrenadoresArchivoTexto(gym);

			break;
		}
	}
}

static void MenuSecundarioAccionSector(Gym* gym, char* accionTexto, int accion)
{
	switch (accion)
	{
		case 0:
		{
			GymAgregarSector(gym);

			break;
		}
		case 1:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			int idsSectores[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionSectores = MENU_EXIT_VALUE;

			opcionSectores = MenuListaSectores(gym, accionTexto, idsSectores);

			if (opcionSectores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymModificarSectorNombre(gym, idsSectores[opcionSectores]);
			
			break;
		}
		case 2:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			GymMostrarSectores(gym);

			break;
		}
		case 3:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			int idsSectores[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionSectores = MENU_EXIT_VALUE;

			opcionSectores = MenuListaSectores(gym, accionTexto, idsSectores);

			if (opcionSectores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymMostrarSector(gym, idsSectores[opcionSectores]);

			break;
		}
		case 4:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			int idsSectores[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionSectores = MENU_EXIT_VALUE;

			opcionSectores = MenuListaSectores(gym, accionTexto, idsSectores);

			if (opcionSectores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarSector(gym, idsSectores[opcionSectores]);

			break;
		}
		case 5:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			GymExportarSectoresArchivoTexto(gym);

			break;
		}
	}
}

static void MenuSecundarioAccionClase(Gym* gym, char* accionTexto, int accion)
{
	switch (accion)
	{
		case 0:
		{
			GymAgregarClase(gym);

			break;
		}
		case 1:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			int idsClases[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionClases = MENU_EXIT_VALUE;

			opcionClases = MenuListaClases(gym, "Clases", idsClases);

			if (opcionClases == MENU_EXIT_VALUE)
			{
				return;
			}

			char textoModificar[][MAX_MENU_TEXT_SIZE] =
			{
				"Nombre",
				"Entrenador",
				"Sector",
				"Clientes",
				"Precio",
				"Hora de inicio",
				"Duracion"
			};

			int opcionModificar = MenuListaCrearMenu(accionTexto, textoModificar, GET_CHARSMAX(textoModificar), 1);

			if (opcionModificar == MENU_EXIT_VALUE)
			{
				return;
			}

			switch (opcionModificar)
			{
				case 0:
				{
					GymModificarClienteNombre(gym, idsClases[opcionClases]);

					break;
				}
				case 1:
				{
					if (GymHayEntrenadores(gym) == 0)
					{
						printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

						return;
					}

					char textoModificarEntrenadores[][MAX_MENU_TEXT_SIZE] =
					{
						"Asignar",
						"Eliminar"
					};

					char titulo[MAX_MENU_TEXT_SIZE];

					snprintf(titulo, MAX_MENU_TEXT_SIZE, "%s %s", accionTexto, textoModificar[opcionModificar]);

					int opcionModificarEntrenadores = MenuListaCrearMenu(titulo, textoModificarEntrenadores, GET_CHARSMAX(textoModificarEntrenadores), 1);

					if (opcionModificarEntrenadores == MENU_EXIT_VALUE)
					{
						return;
					}

					switch (opcionModificarEntrenadores)
					{
						case 0:
						{
							int idsEntrenadores[MAX_MENU_ARRAY_SIZE] = { 0 };
							int opcionEntrenadores = MENU_EXIT_VALUE;

							opcionEntrenadores = MenuListaEntrenadores(gym, "Entrenadores", idsEntrenadores);

							if (opcionEntrenadores == MENU_EXIT_VALUE)
							{
								return;
							}

							GymAsignarEntrenadorClase(gym, idsClases[opcionClases], idsEntrenadores[opcionEntrenadores]);

							break;
						}
						case 1:
						{
							GymEliminarEntrenadorClase(gym, idsClases[opcionClases]);

							break;
						}
					}

					break;
				}
				case 2:
				{
					if (GymHaySectores(gym) == 0)
					{
						printf("[ERROR] No hay sectores para %s\n", accionTexto);

						return;
					}

					char textoModificarSectores[][MAX_MENU_TEXT_SIZE] =
					{
						"Asignar",
						"Eliminar"
					};

					char titulo[MAX_MENU_TEXT_SIZE];

					snprintf(titulo, MAX_MENU_TEXT_SIZE, "%s %s", accionTexto, textoModificar[opcionModificar]);

					int opcionModificarSectores = MenuListaCrearMenu(titulo, textoModificarSectores, GET_CHARSMAX(textoModificarSectores), 1);

					if (opcionModificarSectores == MENU_EXIT_VALUE)
					{
						return;
					}

					switch (opcionModificarSectores)
					{
						case 0:
						{
							int idsSectores[MAX_MENU_ARRAY_SIZE] = { 0 };
							int opcionSectores = MENU_EXIT_VALUE;

							opcionSectores = MenuListaSectores(gym, "Sectores", idsSectores);

							if (opcionSectores == MENU_EXIT_VALUE)
							{
								return;
							}

							GymAsignarSectorClase(gym, idsClases[opcionClases], idsSectores[opcionSectores]);

							break;
						}
						case 1:
						{
							GymEliminarSectorClase(gym, idsClases[opcionClases]);

							break;
						}
					}

					break;
				}
				case 3:
				{
					if (GymHayClientes(gym) == 0)
					{
						printf("[ERROR] No hay clientes para %s\n", accionTexto);

						return;
					}

					char textoModificarClientes[][MAX_MENU_TEXT_SIZE] =
					{
						"Agregar",
						"Eliminar"
					};

					char titulo[MAX_MENU_TEXT_SIZE];

					snprintf(titulo, MAX_MENU_TEXT_SIZE, "%s %s", accionTexto, textoModificar[opcionModificar]);

					int opcionModificarClientes = MenuListaCrearMenu(titulo, textoModificarClientes, GET_CHARSMAX(textoModificarClientes), 1);

					if (opcionModificarClientes == MENU_EXIT_VALUE)
					{
						return;
					}

					switch (opcionModificarClientes)
					{
						case 0:
						{
							int idsClientes[MAX_MENU_ARRAY_SIZE] = { 0 };
							int opcionClientes = MENU_EXIT_VALUE;

							opcionClientes = MenuListaClientes(gym, "Clientes", idsClientes);

							if (opcionClientes == MENU_EXIT_VALUE)
							{
								return;
							}

							GymAgregarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							break;
						}
						case 1:
						{
							if (GymHayClientesEnClase(gym, idsClases[opcionClases]) == 0)
							{
								printf("[ERROR] La clase no tiene ningun cliente asignado\n");

								return;
							}

							char nombresClientes[MAX_ID_CLIENTE_SIZE][MAX_NOMBRE_CLIENTE_SIZE];
							int idsClientes[MAX_ID_CLIENTE_SIZE] = { 0 };
							int clientesSize = 0;
							int opcionClientes = MENU_EXIT_VALUE;

							clientesSize = GymObtenerClaseClientesNombresIds(gym, idsClases[opcionClases], nombresClientes, idsClientes);

							opcionClientes = MenuListaCrearMenu("Clientes", nombresClientes, clientesSize, 1);

							if (opcionClientes == MENU_EXIT_VALUE)
							{
								return;
							}

							GymEliminarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							break;
						}
					}

					break;
				}
				case 4:
				{
					GymAsignarClasePrecio(gym, idsClases[opcionClases]);

					break;
				}
				case 5:
				{
					GymModificarClaseHorario(gym, idsClases[opcionClases]);

					break;
				}
				case 6:
				{
					GymModificarClaseDuracion(gym, idsClases[opcionClases]);

					break;
				}
			}

			break;
		}
		case 2:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			GymMostrarClases(gym);

			break;
		}
		case 3:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			int idsClases[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionClases = MENU_EXIT_VALUE;

			opcionClases = MenuListaClases(gym, "Clases", idsClases);

			if (opcionClases == MENU_EXIT_VALUE)
			{
				return;
			}

			GymMostrarClase(gym, idsClases[opcionClases]);

			break;
		}
		case 4:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			int idsClases[MAX_MENU_ARRAY_SIZE] = { 0 };
			int opcionClases = MENU_EXIT_VALUE;

			opcionClases = MenuListaClases(gym, "Clases", idsClases);

			if (opcionClases == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarClase(gym, idsClases[opcionClases]);

			break;
		}
		case 5:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			GymExportarClasesArchivoTexto(gym);

			break;
		}
	}
}

static void MenuListaAgregarVolver(int pagina)
{
	if (pagina > 1)
	{
		printf("%d. Volver\n", MENU_PREV);
	}
}

static void MenuListaAgregarSiguiente(int size, int pagina)
{
	if (size > MAX_MENU_ITEMS * pagina)
	{
		printf("%d. Siguiente\n", MENU_NEXT);
	}
}

static void MenuListaAgregarSalir(void)
{
	printf("%d. Salir\n\n", MENU_EXIT);
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

static void MenuPausa(void)
{
	printf("\nPresione enter para continuar\n");
	system("pause");
}

static int MenuListaClientes(Gym* gym, char* titulo, int* idsClientes)
{
	char nombresClientes[MAX_MENU_ARRAY_SIZE][MAX_NOMBRE_CLIENTE_SIZE];
	int clientesSize = 0;

	clientesSize = GymObtenerClientesNombresIds(gym, nombresClientes, idsClientes);

	return MenuListaCrearMenu(titulo, nombresClientes, clientesSize, 1);
}

static int MenuListaClases(Gym* gym, char* titulo, int* idsClases)
{
	char nombresClases[MAX_MENU_ARRAY_SIZE][MAX_NOMBRE_CLIENTE_SIZE];
	int clasesSize = 0;

	clasesSize = GymObtenerClasesNombresIds(gym, nombresClases, idsClases);

	return MenuListaCrearMenu(titulo, nombresClases, clasesSize, 1);
}

static int MenuListaEntrenadores(Gym* gym, char* titulo, int* idsEntrenadores)
{
	char nombresEntrenadores[MAX_MENU_ARRAY_SIZE][MAX_NOMBRE_ENTRENADOR_SIZE];
	int entrenadoresSize = 0;

	entrenadoresSize = GymObtenerEntrenadoresNombresIds(gym, nombresEntrenadores, idsEntrenadores);

	return MenuListaCrearMenu(titulo, nombresEntrenadores, entrenadoresSize, 1);
}

static int MenuListaSectores(Gym* gym, char* titulo, int* idsSectores)
{
	char nombresSectores[MAX_MENU_ARRAY_SIZE][MAX_NOMBRE_ENTRENADOR_SIZE];
	int sectoresSize = 0;

	sectoresSize = GymObtenerSectoresNombresIds(gym, nombresSectores, idsSectores);

	return MenuListaCrearMenu(titulo, nombresSectores, sectoresSize, 1);
}