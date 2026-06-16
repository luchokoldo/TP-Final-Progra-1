#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "scanner.h"
#include "utilidades.h"

#define MAX_ARRAY_SIZE	256
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
static int MenuListaEntrenadores(Gym* gym, char* titulo, int* idsEntrenadores);
static int MenuListaClientes(Gym* gym, char* titulo, int* idsClientes);
static int MenuListaClases(Gym* gym, char* titulo, int* idsClases);
static int MenuListaSectores(Gym* gym, char* titulo, int* idsSectores);
static void MenuIngresarNombre(char* nombre, int size);
static void MenuIngresarGenero(char* genero, int size);
static double MenuIngresarPrecio(void);
static void MenuIngresarHorario(int* horas, int* minutos);
static void MenuIngresarDuracion(int* horas, int* minutos);
static void MenuModificarNombre(char* nombreViejo, char* nombreNuevo, int size);
static void MenuModificarGenero(char* generoViejo, char* generoNuevo, int size);
static double MenuModificarPrecio(double precioViejo);
static void MenuModificarHorario(int horasViejo, int minutosViejo, int* horas, int* minutos);
static void MenuModificarDuracion(int horasViejo, int minutosViejo, int* horas, int* minutos);

static int MenuCrearEntrenador(Gym* gym);
static int MenuCrearSector(Gym* gym);
static int MenuCrearCliente(Gym* gym);
static int MenuCrearClase(Gym* gym);

static void MenuMostrarClases(Gym* gym);
static void MenuMostrarClase(Gym* gym, int idClase);
static void MenuMostrarSectores(Gym* gym);
static void MenuMostrarSector(Gym* gym, int idSector);
static void MenuMostrarEntrenadores(Gym* gym);
static void MenuMostrarEntrenador(Gym* gym, int idEntrenador);
static void MenuMostrarClientes(Gym* gym);
static void MenuMostrarCliente(Gym* gym, int idCliente);
static void MenuMostrarClasesDelDia(Gym* gym);

void MenuMostrarMenu(Gym* gym)
{
	int opcion = MENU_EXIT_VALUE;

	char texto[][MAX_MENU_TEXT_SIZE] =
	{
		"Mostrar Clases del dia",
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
			int opcionSecundario = 0;
			
			switch (opcion)
			{
				case 0:
				{
					MenuMostrarClasesDelDia(gym);

					break;
				}
				default:
				{
					opcionSecundario = MenuMostrarMenuSecundario(gym, texto[opcion], opcion);
				}
			}

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
		case 1:
			MenuSecundarioAccionCliente(gym, texto[opcion], opcion);
			break;
		case 2:
			MenuSecundarioAccionEntrenador(gym, texto[opcion], opcion);
			break;
		case 3:
			MenuSecundarioAccionSector(gym, texto[opcion], opcion);
			break;
		case 4:
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
			int exito = MenuCrearCliente(gym);

			if (exito && exito != ID_INVALIDO)
			{
				printf("Cliente creado con exito.\n");
			}

			break;
		}
		case 1: 
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			int idsClientes[MAX_ARRAY_SIZE] = { 0 };
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
				{
					char nombreViejo[MAX_NOMBRE_SIZE];
					char nombreNuevo[MAX_NOMBRE_SIZE];

					GymObtenerClienteNombre(gym, idsClientes[opcionClientes], nombreViejo);
					MenuModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_SIZE);

					if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
					{
						return;
					}

					GymModificarClienteNombre(gym, idsClientes[opcionClientes], nombreNuevo);

					printf("Nombre modificado con exito.\n");

					break;
				}
				case 1:
				{
					char generoViejo[MAX_GENERO_SIZE];
					char generoNuevo[MAX_GENERO_SIZE];

					GymObtenerClienteGenero(gym, idsClientes[opcionClientes], generoViejo);
					MenuModificarGenero(generoViejo, generoNuevo, MAX_GENERO_SIZE);

					if (*generoNuevo == '\0' || strcmp(generoNuevo, generoViejo) == 0)
					{
						return;
					}

					GymModificarClienteGenero(gym, idsClientes[opcionClientes], generoNuevo);

					printf("Genero modificado con exito.\n");

					break;
				}
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
							int idsClases[MAX_ARRAY_SIZE] = { 0 };
							int opcionClases = MENU_EXIT_VALUE;

							opcionClases = MenuListaClases(gym, "Clases", idsClases);

							if (opcionClases == MENU_EXIT_VALUE)
							{
								return;
							}

							int exito = GymAgregarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							if (exito && exito != ID_INVALIDO)
							{
								printf("Clase agregada con exito.\n");
							}

							break;
						}
						case 1:
						{
							if (GymHayClasesEnCliente(gym, idsClientes[opcionClientes]) == 0)
							{
								printf("[ERROR] El cliente no tiene ninguna clase asignada.\n");

								return;
							}

							char nombresClases[MAX_IDS][MAX_NOMBRE_SIZE];
							int idsClases[MAX_IDS] = { 0 };
							int clasesSize = 0;
							int opcionClases = MENU_EXIT_VALUE;
				
							clasesSize = GymObtenerClienteClasesNombresIds(gym, idsClientes[opcionClientes], nombresClases, idsClases);

							opcionClases = MenuListaCrearMenu("Clases", nombresClases, clasesSize, 1);

							if (opcionClases == MENU_EXIT_VALUE)
							{
								return;
							}

							GymEliminarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							printf("Clase eliminada con exito.\n");

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

			MenuMostrarClientes(gym);

			break;
		}
		case 3:
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			int idsClientes[MAX_ARRAY_SIZE] = { 0 };
			int opcionClientes = MENU_EXIT_VALUE;

			opcionClientes = MenuListaClientes(gym, accionTexto, idsClientes);

			if (opcionClientes == MENU_EXIT_VALUE)
			{
				return;
			}

			MenuMostrarCliente(gym, idsClientes[opcionClientes]);

			break;
		}
		case 4:
		{
			if (GymHayClientes(gym) == 0)
			{
				printf("[ERROR] No hay clientes para %s\n", accionTexto);

				return;
			}

			int idsClientes[MAX_ARRAY_SIZE] = { 0 };
			int opcionClientes = MENU_EXIT_VALUE;

			opcionClientes = MenuListaClientes(gym, accionTexto, idsClientes);

			if (opcionClientes == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarCliente(gym, idsClientes[opcionClientes]);

			printf("Cliente eliminado con exito.\n");

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

			printf("Cliente exportado con exito.\n");

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
			int exito = MenuCrearEntrenador(gym);

			if (exito && exito != ID_INVALIDO)
			{
				printf("Entrenador creado con exito.\n");
			}

			break;
		}
		case 1:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
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
				{
					char nombreViejo[MAX_NOMBRE_SIZE];
					char nombreNuevo[MAX_NOMBRE_SIZE];

					GymObtenerEntrenadorNombre(gym, idsEntrenadores[opcionEntrenadores], nombreViejo);
					MenuModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_SIZE);

					if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
					{
						return;
					}
					
					GymModificarEntrenadorNombre(gym, idsEntrenadores[opcionEntrenadores], nombreNuevo);

					printf("Nombre modificado con exito.\n");

					break;
				}
				case 1:
				{
					char generoViejo[MAX_GENERO_SIZE];
					char generoNuevo[MAX_GENERO_SIZE];

					GymObtenerEntrenadorGenero(gym, idsEntrenadores[opcionEntrenadores], generoViejo);
					MenuModificarGenero(generoViejo, generoNuevo, MAX_GENERO_SIZE);

					if (*generoNuevo == '\0' || strcmp(generoNuevo, generoViejo) == 0)
					{
						return;
					}
					
					GymModificarEntrenadorGenero(gym, idsEntrenadores[opcionEntrenadores], generoNuevo);

					printf("Genero modificado con exito.\n");

					break;
				}
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

			MenuMostrarEntrenadores(gym);

			break;
		}
		case 3:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
			int opcionEntrenadores = MENU_EXIT_VALUE;

			opcionEntrenadores = MenuListaEntrenadores(gym, accionTexto, idsEntrenadores);

			if (opcionEntrenadores == MENU_EXIT_VALUE)
			{
				return;
			}

			MenuMostrarEntrenador(gym, idsEntrenadores[opcionEntrenadores]);

			break;
		}
		case 4:
		{
			if (GymHayEntrenadores(gym) == 0)
			{
				printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

				return;
			}

			int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
			int opcionEntrenadores = MENU_EXIT_VALUE;

			opcionEntrenadores = MenuListaEntrenadores(gym, accionTexto, idsEntrenadores);

			if (opcionEntrenadores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarEntrenador(gym, idsEntrenadores[opcionEntrenadores]);

			printf("Entrenador eliminado con exito.\n");

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

			printf("Entrenador exportado con exito.\n");

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
			int exito = MenuCrearSector(gym);

			if(exito && exito != ID_INVALIDO)
			{
				printf("Sector creado con exito.\n");
			}

			break;
		}
		case 1:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			int idsSectores[MAX_ARRAY_SIZE] = { 0 };
			int opcionSectores = MENU_EXIT_VALUE;

			opcionSectores = MenuListaSectores(gym, accionTexto, idsSectores);

			if (opcionSectores == MENU_EXIT_VALUE)
			{
				return;
			}

			char nombreViejo[MAX_NOMBRE_SIZE];
			char nombreNuevo[MAX_NOMBRE_SIZE];

			GymObtenerSectorNombre(gym, idsSectores[opcionSectores], nombreViejo);
			MenuModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_SIZE);

			if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
			{
				return;
			}

			GymModificarSectorNombre(gym, idsSectores[opcionSectores], nombreNuevo);

			printf("Nombre modificado con exito.\n");
			
			break;
		}
		case 2:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			MenuMostrarSectores(gym);

			break;
		}
		case 3:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			int idsSectores[MAX_ARRAY_SIZE] = { 0 };
			int opcionSectores = MENU_EXIT_VALUE;

			opcionSectores = MenuListaSectores(gym, accionTexto, idsSectores);

			if (opcionSectores == MENU_EXIT_VALUE)
			{
				return;
			}

			MenuMostrarSector(gym, idsSectores[opcionSectores]);

			break;
		}
		case 4:
		{
			if (GymHaySectores(gym) == 0)
			{
				printf("[ERROR] No hay sectores para %s\n", accionTexto);

				return;
			}

			int idsSectores[MAX_ARRAY_SIZE] = { 0 };
			int opcionSectores = MENU_EXIT_VALUE;

			opcionSectores = MenuListaSectores(gym, accionTexto, idsSectores);

			if (opcionSectores == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarSector(gym, idsSectores[opcionSectores]);

			printf("Sector eliminado con exito.\n");

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

			printf("Sector exportado con exito.\n");

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
			int exito = MenuCrearClase(gym);

			if (exito && exito != ID_INVALIDO)
			{
				printf("Clase creada con exito.\n");
			}

			break;
		}
		case 1:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			int idsClases[MAX_ARRAY_SIZE] = { 0 };
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
					char nombreViejo[MAX_NOMBRE_SIZE];
					char nombreNuevo[MAX_NOMBRE_SIZE];

					GymObtenerClaseNombre(gym, idsClases[opcionClases], nombreViejo);
					MenuModificarNombre(nombreViejo, nombreNuevo, MAX_NOMBRE_SIZE);

					if (*nombreNuevo == '\0' || strcmp(nombreNuevo, nombreViejo) == 0)
					{
						return;
					}

					GymModificarClaseNombre(gym, idsClases[opcionClases], nombreNuevo);

					printf("Nombre modificado con exito.\n");

					break;
				}
				case 1:
				{
					if (GymHayEntrenadores(gym) == 0)
					{
						printf("[ERROR] No hay entrenadores para %s\n", accionTexto);

						int idEntrenador = MenuCrearEntrenador(gym);

						if (idEntrenador == ID_INVALIDO)
						{
							return;
						}

						GymAsignarEntrenadorClase(gym, idsClases[opcionClases], idEntrenador);

						printf("Entrenador asignado con exito.\n");

						return;
					}

					char textoModificarEntrenadores[][MAX_MENU_TEXT_SIZE] =
					{
						"Nuevo",
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
							int idEntrenador = MenuCrearEntrenador(gym);

							if (idEntrenador == ID_INVALIDO)
							{
								return;
							}

							GymAsignarEntrenadorClase(gym, idsClases[opcionClases], idEntrenador);

							printf("Entrenador asignado con exito.\n");

							break;
						}
						case 1:
						{
							int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
							int opcionEntrenadores = MENU_EXIT_VALUE;

							opcionEntrenadores = MenuListaEntrenadores(gym, "Entrenadores", idsEntrenadores);

							if (opcionEntrenadores == MENU_EXIT_VALUE)
							{
								return;
							}

							GymAsignarEntrenadorClase(gym, idsClases[opcionClases], idsEntrenadores[opcionEntrenadores]);

							printf("Entrenador asignado con exito.\n");

							break;
						}
						case 2:
						{
							GymEliminarEntrenadorClase(gym, idsClases[opcionClases]);

							printf("Entrenador removido con exito.\n");

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

						int idSector = MenuCrearSector(gym);

						if (idSector == ID_INVALIDO)
						{
							return;
						}

						GymAsignarSectorClase(gym, idsClases[opcionClases], idSector);

						printf("Sector asignado con exito.\n");

						return;
					}

					char textoModificarSectores[][MAX_MENU_TEXT_SIZE] =
					{
						"Nuevo",
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
							int idSector = MenuCrearSector(gym);

							if (idSector == ID_INVALIDO)
							{
								return;
							}

							GymAsignarSectorClase(gym, idsClases[opcionClases], idSector);

							printf("Sector asignado con exito.\n");

							break;
						}
						case 1:
						{
							int idsSectores[MAX_ARRAY_SIZE] = { 0 };
							int opcionSectores = MENU_EXIT_VALUE;

							opcionSectores = MenuListaSectores(gym, "Sectores", idsSectores);

							if (opcionSectores == MENU_EXIT_VALUE)
							{
								return;
							}

							GymAsignarSectorClase(gym, idsClases[opcionClases], idsSectores[opcionSectores]);

							printf("Sector asignado con exito.\n");

							break;
						}
						case 2:
						{
							GymEliminarSectorClase(gym, idsClases[opcionClases]);

							printf("Sector removido con exito.\n");

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

						int idCliente = MenuCrearCliente(gym);

						if (idCliente == ID_INVALIDO)
						{
							return;
						}

						int exito = GymAgregarClienteClase(gym, idCliente, idsClases[opcionClases]);

						if (exito && exito != ID_INVALIDO)
						{
							printf("Cliente agregado con exito.\n");
						}

						return;
					}

					char textoModificarClientes[][MAX_MENU_TEXT_SIZE] =
					{
						"Nuevo",
						"Asignar",
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
							int idCliente = MenuCrearCliente(gym);

							if (idCliente == ID_INVALIDO)
							{
								return;
							}

							int exito = GymAgregarClienteClase(gym, idCliente, idsClases[opcionClases]);

							if (exito && exito != ID_INVALIDO)
							{
								printf("Cliente agregado con exito.\n");
							}

							break;
						}
						case 1:
						{
							int idsClientes[MAX_ARRAY_SIZE] = { 0 };
							int opcionClientes = MENU_EXIT_VALUE;

							opcionClientes = MenuListaClientes(gym, "Clientes", idsClientes);

							if (opcionClientes == MENU_EXIT_VALUE)
							{
								return;
							}

							int exito = GymAgregarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							if(exito && exito != ID_INVALIDO)
							{
								printf("Cliente agregado con exito.\n");
							}

							break;
						}
						case 2:
						{
							if (GymHayClientesEnClase(gym, idsClases[opcionClases]) == 0)
							{
								printf("[ERROR] La clase no tiene ningun cliente asignado\n");

								return;
							}

							char nombresClientes[MAX_IDS][MAX_NOMBRE_SIZE];
							int idsClientes[MAX_IDS] = { 0 };
							int clientesSize = 0;
							int opcionClientes = MENU_EXIT_VALUE;

							clientesSize = GymObtenerClaseClientesNombresIds(gym, idsClases[opcionClases], nombresClientes, idsClientes);

							opcionClientes = MenuListaCrearMenu("Clientes", nombresClientes, clientesSize, 1);

							if (opcionClientes == MENU_EXIT_VALUE)
							{
								return;
							}

							GymEliminarClienteClase(gym, idsClientes[opcionClientes], idsClases[opcionClases]);

							printf("Cliente removido con exito.\n");

							break;
						}
					}

					break;
				}
				case 4:
				{
					double precioViejo = GymObtenerClasePrecio(gym, idsClases[opcionClases]);
					double precioNuevo = 0.0;

					do
					{
						precioNuevo = MenuModificarPrecio(precioViejo);

						if (precioNuevo < 0 && precioNuevo != -1)
						{
							printf("[ERROR] El precio tiene que ser mayor o igual a 0\n");
						}
					} while (precioNuevo < 0 && precioNuevo != -1);

					if (precioNuevo == -1)
					{
						return;
					}

					GymAsignarClasePrecio(gym, idsClases[opcionClases], precioNuevo);

					printf("Precio asignado con exito.\n");

					break;
				}
				case 5:
				{
					int inicioHoras = 0;
					int inicioMinutos = 0;
					int inicioHorasViejo = 0;
					int inicioMinutosViejo = 0;

					GymObtenerClaseHorario(gym, idsClases[opcionClases], &inicioHorasViejo, &inicioMinutosViejo);

					do
					{
						MenuModificarHorario(inicioHorasViejo, inicioMinutosViejo, &inicioHoras, &inicioMinutos);

						inicioHoras += inicioMinutos / 60;
						inicioMinutos %= 60;

						if (inicioHoras < 0)
						{
							printf("[ERROR] La hora no pueden ser menor a 0\n");
						}
						else if (inicioMinutos < 0)
						{
							printf("[ERROR] Los minutos no pueden ser menor a 0\n");
						}
						else if (inicioHoras > 24)
						{
							printf("[ERROR] La hora no pueden ser mayor a 24\n");
						}
					} while (inicioHoras < 0 || inicioMinutos < 0 || inicioHoras > 24);
					
					int exito = GymModificarClaseHorario(gym, idsClases[opcionClases], inicioHoras, inicioMinutos);

					if (exito && exito != ID_INVALIDO)
					{
						printf("Horario modificado con exito.\n");
					}

					break;
				}
				case 6:
				{
					int duracionHoras = 0;
					int duracionMinutos = 0;
					int horasViejo = 0;
					int minutosViejo = 0;

					GymObtenerClaseDuracion(gym, idsClases[opcionClases], &horasViejo, &minutosViejo);

					do
					{
						MenuModificarDuracion(horasViejo, minutosViejo, &duracionHoras, &duracionMinutos);
						
						duracionHoras += duracionMinutos / 60;
						duracionMinutos %= 60;

						if (duracionHoras < 0)
						{
							printf("[ERROR] La hora no pueden ser menor a 0\n");
						}
						else if (duracionMinutos < 0)
						{
							printf("[ERROR] Los minutos no pueden ser menor a 0\n");
						}
						else if ((duracionHoras * 60 + duracionMinutos) < MIN_DURACION_CLASE)
						{
							printf("[ERROR] La duracion de la clase no puede ser menor a %d minutos\n", MIN_DURACION_CLASE);
						}
					} while (duracionHoras < 0 || duracionMinutos < 0 || (duracionHoras * 60 + duracionMinutos) < MIN_DURACION_CLASE);
					
					int exito = GymModificarClaseDuracion(gym, idsClases[opcionClases], duracionHoras, duracionMinutos);

					if (exito && exito != ID_INVALIDO)
					{
						printf("Duracion modificado con exito.\n");
					}

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

			MenuMostrarClases(gym);

			break;
		}
		case 3:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			int idsClases[MAX_ARRAY_SIZE] = { 0 };
			int opcionClases = MENU_EXIT_VALUE;

			opcionClases = MenuListaClases(gym, "Clases", idsClases);

			if (opcionClases == MENU_EXIT_VALUE)
			{
				return;
			}

			MenuMostrarClase(gym, idsClases[opcionClases]);

			break;
		}
		case 4:
		{
			if (GymHayClases(gym) == 0)
			{
				printf("[ERROR] No hay clases para %s\n", accionTexto);

				return;
			}

			int idsClases[MAX_ARRAY_SIZE] = { 0 };
			int opcionClases = MENU_EXIT_VALUE;

			opcionClases = MenuListaClases(gym, "Clases", idsClases);

			if (opcionClases == MENU_EXIT_VALUE)
			{
				return;
			}

			GymEliminarClase(gym, idsClases[opcionClases]);

			printf("Clase eliminada con exito.\n");

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

			printf("Archivo exportado con exito.\n");

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
	char nombresClientes[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int clientesSize = 0;

	clientesSize = GymObtenerClientesNombresIds(gym, nombresClientes, idsClientes);

	return MenuListaCrearMenu(titulo, nombresClientes, clientesSize, 1);
}

static int MenuListaClases(Gym* gym, char* titulo, int* idsClases)
{
	char nombresClases[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int clasesSize = 0;

	clasesSize = GymObtenerClasesNombresIds(gym, nombresClases, idsClases);

	return MenuListaCrearMenu(titulo, nombresClases, clasesSize, 1);
}

static int MenuListaEntrenadores(Gym* gym, char* titulo, int* idsEntrenadores)
{
	char nombresEntrenadores[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int entrenadoresSize = 0;

	entrenadoresSize = GymObtenerEntrenadoresNombresIds(gym, nombresEntrenadores, idsEntrenadores);

	return MenuListaCrearMenu(titulo, nombresEntrenadores, entrenadoresSize, 1);
}

static int MenuListaSectores(Gym* gym, char* titulo, int* idsSectores)
{
	char nombresSectores[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int sectoresSize = 0;

	sectoresSize = GymObtenerSectoresNombresIds(gym, nombresSectores, idsSectores);

	return MenuListaCrearMenu(titulo, nombresSectores, sectoresSize, 1);
}

static void MenuIngresarNombre(char* nombre, int size)
{
	printf("\nIngrese nombre: ");
	ScannerString(nombre, size);

	snprintf(nombre, size, "%s", UtilidadesStringTrim(nombre));
}

static void MenuIngresarGenero(char* genero, int size)
{
	printf("\nIngrese genero: ");
	ScannerString(genero, size);

	snprintf(genero, size, "%s", UtilidadesStringTrim(genero));
}

static double MenuIngresarPrecio()
{
	printf("\nIngrese precio: $");
	double precio = ScannerDouble();

	return precio;
}

static void MenuIngresarHorario(int* horas, int* minutos)
{
	printf("\nIngrese hora de inicio: ");
	*horas = ScannerInt();

	printf("Ingrese minuto de inicio: ");
	*minutos = ScannerInt();
}

static void MenuIngresarDuracion(int* horas, int* minutos)
{
	printf("\nIngrese horas de duracion: ");
	*horas = ScannerInt();

	printf("Ingrese minutos de duracion: ");
	*minutos = ScannerInt();
}

static void MenuModificarNombre(char* nombreViejo, char* nombreNuevo, int size)
{
	printf("\nNombre actual: %s\n", nombreViejo);

	printf("Ingresar nuevo nombre (vacio para cancelar): ");
	ScannerString(nombreNuevo, size);

	snprintf(nombreNuevo, size, "%s", UtilidadesStringTrim(nombreNuevo));
}

static void MenuModificarGenero(char* generoViejo, char* generoNuevo, int size)
{
	printf("\nGenero actual: %s\n", generoViejo);

	printf("Ingresar nuevo genero (vacio para cancelar): ");
	ScannerString(generoNuevo, size);

	snprintf(generoNuevo, size, "%s", UtilidadesStringTrim(generoNuevo));
}

static double MenuModificarPrecio(double precioViejo)
{
	printf("\nPrecio actual: %.2f\n", precioViejo);

	printf("Ingresar nuevo precio (-1 para cancelar): ");
	double precio = ScannerDouble();

	return precio;
}

static void MenuModificarHorario(int horasViejo, int minutosViejo, int* horas, int* minutos)
{
	printf("\nHorario actual: %d:%d\n", horasViejo, minutosViejo);

	printf("Ingrese nueva hora de inicio: ");
	*horas = ScannerInt();

	printf("Ingrese minuto de inicio: ");
	*minutos = ScannerInt();
}

static void MenuModificarDuracion(int horasViejo, int minutosViejo, int* horas, int* minutos)
{
	printf("\nDuracion actual: %d:%d\n", horasViejo, minutosViejo);

	printf("Ingrese horas de duracion: ");
	*horas = ScannerInt();

	printf("Ingrese minutos de duracion: ");
	*minutos = ScannerInt();
}

static int MenuCrearEntrenador(Gym* gym)
{
	char nombre[MAX_NOMBRE_SIZE];
	char genero[MAX_GENERO_SIZE];

	do
	{
		MenuIngresarNombre(nombre, MAX_NOMBRE_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	do
	{
		MenuIngresarGenero(genero, MAX_GENERO_SIZE);

		if (*genero == '\0')
		{
			printf("[ERROR] El genero no puede estar vacio\n");
		}
	} while (*genero == '\0');

	return GymAgregarEntrenador(gym, nombre, genero);
}

static int MenuCrearSector(Gym* gym)
{
	char nombre[MAX_NOMBRE_SIZE];

	do
	{
		MenuIngresarNombre(nombre, MAX_NOMBRE_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	return GymAgregarSector(gym, nombre);
}

static int MenuCrearCliente(Gym* gym)
{
	char nombre[MAX_NOMBRE_SIZE];
	char genero[MAX_GENERO_SIZE];

	do
	{
		MenuIngresarNombre(nombre, MAX_NOMBRE_SIZE);

		if (*nombre == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombre == '\0');

	do
	{
		MenuIngresarGenero(genero, MAX_GENERO_SIZE);

		if (*genero == '\0')
		{
			printf("[ERROR] El genero no puede estar vacio\n");
		}
	} while (*genero == '\0');

	return GymAgregarCliente(gym, nombre, genero);
}

static int MenuCrearClase(Gym* gym)
{
	char nombreClase[MAX_NOMBRE_SIZE];
	int idEntrenador = ID_INVALIDO;
	int idSector = ID_INVALIDO;
	double precio = 0.0;
	int inicioHoras = 0;
	int inicioMinutos = 0;
	int duracionHoras = 0;
	int duracionMinutos = 0;

	do
	{
		MenuIngresarNombre(nombreClase, MAX_NOMBRE_SIZE);

		if (*nombreClase == '\0')
		{
			printf("[ERROR] El nombre no puede estar vacio\n");
		}
	} while (*nombreClase == '\0');

	if (GymHayEntrenadores(gym) == 0)
	{
		printf("[ERROR] No hay entrenadores.\nCreando nuevo entrenador");
		
		idEntrenador = MenuCrearEntrenador(gym);
	}
	else
	{
		int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
		int opcionEntrenadores = MENU_EXIT_VALUE;

		opcionEntrenadores = MenuListaEntrenadores(gym, "Asignar Entrenador", idsEntrenadores);

		if (opcionEntrenadores == MENU_EXIT_VALUE)
		{
			return 0;
		}

		idEntrenador = idsEntrenadores[opcionEntrenadores];
	}

	if (GymHaySectores(gym) == 0)
	{
		printf("[ERROR] No hay sectores.\nCreando nuevo sector");
		
		idSector = MenuCrearSector(gym);
	}
	else
	{
		int idsSectores[MAX_ARRAY_SIZE] = { 0 };
		int opcionSectores = MENU_EXIT_VALUE;

		opcionSectores = MenuListaSectores(gym, "Asignar Sector", idsSectores);

		if (opcionSectores == MENU_EXIT_VALUE)
		{
			return 0;
		}

		idSector = idsSectores[opcionSectores];
	}

	do
	{
		precio = MenuIngresarPrecio();

		if (precio < 0)
		{
			printf("[ERROR] El precio no puede ser menor a 0\n");
		}
	} while (precio < 0);

	do
	{
		MenuIngresarHorario(&inicioHoras, &inicioMinutos);

		inicioHoras += inicioMinutos / 60;
		inicioMinutos %= 60;

		if (inicioHoras < 0)
		{
			printf("[ERROR] La hora no pueden ser menor a 0\n");
		}
		else if (inicioMinutos < 0)
		{
			printf("[ERROR] Los minutos no pueden ser menor a 0\n");
		}
		else if (inicioHoras > 24)
		{
			printf("[ERROR] La hora no pueden ser mayor a 24\n");
		}
	} while (inicioHoras < 0 || inicioMinutos < 0 || inicioHoras > 24);

	do
	{
		MenuIngresarDuracion(&duracionHoras, &duracionMinutos);

		duracionHoras += duracionMinutos / 60;
		duracionMinutos %= 60;

		if (duracionHoras < 0)
		{
			printf("[ERROR] La hora no pueden ser menor a 0\n");
		}
		else if (duracionMinutos < 0)
		{
			printf("[ERROR] Los minutos no pueden ser menor a 0\n");
		}
		else if ((duracionHoras * 60 + duracionMinutos) < MIN_DURACION_CLASE)
		{
			printf("[ERROR] La duracion de la clase no puede ser menor a %d minutos\n", MIN_DURACION_CLASE);
		}
	} while (duracionHoras < 0 || duracionMinutos < 0 || (duracionHoras * 60 + duracionMinutos) < MIN_DURACION_CLASE);

	return GymAgregarClase(gym, nombreClase, idEntrenador, idSector, inicioHoras, inicioMinutos, duracionHoras, duracionMinutos, precio);
}

static void MenuMostrarClases(Gym* gym)
{
	int idsClases[MAX_ARRAY_SIZE] = { 0 };
	char nombresClases[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int clasesSize = 0;

	clasesSize = GymObtenerClasesNombresIds(gym, nombresClases, idsClases);
	
	int idEntrenador = ID_INVALIDO;
	int idSector = ID_INVALIDO;
	int idsClientes[MAX_IDS] = { 0 };
	char nombreEntrenador[MAX_NOMBRE_SIZE];
	char nombreSector[MAX_NOMBRE_SIZE];
	char nombresClientes[MAX_IDS][MAX_NOMBRE_SIZE];
	int clientesSize = 0;
	double precio = 0.0;
	int horaInicio = 0;
	int minutosInicio = 0;
	int horaDuracion = 0;
	int minutosDuracion = 0;

	printf("\n-------------------------------------\n\n");

	for (int i = 0; i < clasesSize; i++)
	{
		printf("Id de la clase: %d\n", idsClases[i]);
		printf("Clase: %s\n", nombresClases[i]);

		idEntrenador = GymObtenerClaseEntrenadorId(gym, idsClases[i]);
		GymObtenerEntrenadorNombre(gym, idEntrenador, nombreEntrenador);

		printf("Entrenador: %s\n", nombreEntrenador);
		
		idSector = GymObtenerClaseSectorId(gym, idsClases[i]);
		GymObtenerSectorNombre(gym, idSector, nombreSector);

		printf("Sector: %s\n", nombreSector);
		printf("Clientes: ");

		clientesSize = GymObtenerClaseClientesNombresIds(gym, idsClases[i], nombresClientes, idsClientes);

		if (clientesSize > 0)
		{
			for (int j = 0; j < clientesSize; j++)
			{
				printf("%s, ", nombresClientes[j]);
			}

			printf("\b\b. \n");
		}
		else
		{
			printf("Sin clientes asignados.\n");
		}

		precio = GymObtenerClasePrecio(gym, idsClases[i]);

		printf("Precio: $%.2f\n", precio);

		GymObtenerClaseHorario(gym, idsClases[i], &horaInicio, &minutosInicio);

		printf("Hora de inicio: %02d:%02d\n", horaInicio, minutosInicio);

		GymObtenerClaseDuracion(gym, idsClases[i], &horaDuracion, &minutosDuracion);

		printf("Duracion: %02d:%02d\n\n", horaDuracion, minutosDuracion);
	}

	printf("--------------------------------------\n");
}

static void MenuMostrarClase(Gym* gym, int idClase)
{
	char nombreClase[MAX_NOMBRE_SIZE];
	int idEntrenador = ID_INVALIDO;
	int idSector = ID_INVALIDO;
	int idsClientes[MAX_IDS] = { 0 };
	char nombreEntrenador[MAX_NOMBRE_SIZE];
	char nombreSector[MAX_NOMBRE_SIZE];
	char nombresClientes[MAX_IDS][MAX_NOMBRE_SIZE];
	int clientesSize = 0;
	double precio = 0.0;
	int horaInicio = 0;
	int minutosInicio = 0;
	int horaDuracion = 0;
	int minutosDuracion = 0;

	printf("\n-------------------------------------\n\n");

	printf("Id de la clase: %d\n", idClase);

	GymObtenerClaseNombre(gym, idClase, nombreClase);

	printf("Clase: %s\n", nombreClase);

	idEntrenador = GymObtenerClaseEntrenadorId(gym, idClase);
	GymObtenerEntrenadorNombre(gym, idEntrenador, nombreEntrenador);

	printf("Entrenador: %s\n", nombreEntrenador);

	idSector = GymObtenerClaseSectorId(gym, idClase);
	GymObtenerSectorNombre(gym, idSector, nombreSector);

	printf("Sector: %s\n", nombreSector);
	printf("Clientes: ");

	clientesSize = GymObtenerClaseClientesNombresIds(gym, idClase, nombresClientes, idsClientes);

	if (clientesSize > 0)
	{
		for (int j = 0; j < clientesSize; j++)
		{
			printf("%s, ", nombresClientes[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clientes asignados.\n");
	}

	precio = GymObtenerClasePrecio(gym, idClase);

	printf("Precio: $%.2f\n", precio);

	GymObtenerClaseHorario(gym, idClase, &horaInicio, &minutosInicio);

	printf("Hora de inicio: %02d:%02d\n", horaInicio, minutosInicio);

	GymObtenerClaseDuracion(gym, idClase, &horaDuracion, &minutosDuracion);

	printf("Duracion: %02d:%02d\n", horaDuracion, minutosDuracion);

	printf("\n--------------------------------------\n");
}

static void MenuMostrarSectores(Gym* gym)
{
	int idsSectores[MAX_ARRAY_SIZE] = { 0 };
	char nombresSectores[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int sectoresSize = 0;

	sectoresSize = GymObtenerSectoresNombresIds(gym, nombresSectores, idsSectores);

	printf("\n--------------------------------------\n\n");

	for (int i = 0; i < sectoresSize; i++)
	{
		printf("ID: %d\n", idsSectores[i]);
		printf("Nombre: %s\n\n", nombresSectores[i]);
	}

	printf("--------------------------------------\n");
}

static void MenuMostrarSector(Gym* gym, int idSector)
{
	char nombreSector[MAX_NOMBRE_SIZE];

	GymObtenerSectorNombre(gym, idSector, nombreSector);
	
	printf("\n--------------------------------------\n\n");
	printf("ID: %d\n", idSector);
	printf("Nombre: %s\n", nombreSector);
	printf("\n--------------------------------------\n");
}

static void MenuMostrarEntrenadores(Gym* gym)
{
	int idsEntrenadores[MAX_ARRAY_SIZE] = { 0 };
	char nombresEntrenadores[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int entrenadoresSize = 0;
	char generoEntrenador[MAX_NOMBRE_SIZE];

	entrenadoresSize = GymObtenerEntrenadoresNombresIds(gym, nombresEntrenadores, idsEntrenadores);

	printf("\n--------------------------------------\n\n");
	
	for (int i = 0; i < entrenadoresSize; i++)
	{
		printf("ID: %d\n", idsEntrenadores[i]);
		printf("Nombre: %s\n", nombresEntrenadores[i]);

		GymObtenerEntrenadorGenero(gym, idsEntrenadores[i], generoEntrenador);

		printf("Genero: %s\n\n", generoEntrenador);
	}

	printf("--------------------------------------\n");
}

static void MenuMostrarEntrenador(Gym* gym, int idEntrenador)
{
	char NombreEntrenador[MAX_NOMBRE_SIZE];
	char generoEntrenador[MAX_NOMBRE_SIZE];

	GymObtenerEntrenadorNombre(gym, idEntrenador, NombreEntrenador);
	GymObtenerEntrenadorGenero(gym, idEntrenador, generoEntrenador);
	
	printf("\n--------------------------------------\n\n");

	printf("ID: %d\n", idEntrenador);
	printf("Nombre: %s\n", NombreEntrenador);
	printf("Genero: %s\n", generoEntrenador);

	printf("\n--------------------------------------\n");
}

static void MenuMostrarClientes(Gym* gym)
{
	int idsClientes[MAX_ARRAY_SIZE] = { 0 };
	char nombresClientes[MAX_ARRAY_SIZE][MAX_NOMBRE_SIZE];
	int clientesSize = 0;

	clientesSize = GymObtenerClientesNombresIds(gym, nombresClientes, idsClientes);

	char generoCliente[MAX_GENERO_SIZE];
	char nombresClases[MAX_IDS][MAX_NOMBRE_SIZE];
	int idsClases[MAX_IDS] = { 0 };
	int clasesSize = 0;
	double MontoTotal = 0.0;

	printf("\n--------------------------------------\n\n");

	for (int i = 0; i < clientesSize; i++)
	{
		printf("ID: %d\n", idsClientes[i]);
		printf("Nombre: %s\n", nombresClientes[i]);

		GymObtenerClienteGenero(gym, idsClientes[i], generoCliente);

		printf("Genero: %s\n", generoCliente);
		printf("Clases: ");

		clasesSize = GymObtenerClienteClasesNombresIds(gym, idsClientes[i], nombresClases, idsClases);

		if (clasesSize > 0)
		{
			for (int j = 0; j < clasesSize; j++)
			{
				printf("%s, ", nombresClases[j]);
			}

			printf("\b\b. \n");
		}
		else
		{
			printf("Sin clases asignadas.\n");
		}

		MontoTotal = GymObtenerClienteMontoTotalClases(gym, idsClientes[i]);

		printf("Monto a Abonar: $%.2f\n\n", MontoTotal);
	}

	printf("--------------------------------------\n");
}

static void MenuMostrarCliente(Gym* gym, int idCliente)
{
	char nombreCliente[MAX_NOMBRE_SIZE];
	char generoCliente[MAX_GENERO_SIZE];
	char nombresClases[MAX_IDS][MAX_NOMBRE_SIZE];
	int idsClases[MAX_IDS] = { 0 };
	int clasesSize = 0;
	double MontoTotal = 0.0;
	
	printf("\n--------------------------------------\n\n");

	printf("ID: %d\n", idCliente);

	GymObtenerClienteNombre(gym, idCliente, nombreCliente);

	printf("Nombre: %s\n", nombreCliente);

	GymObtenerClienteGenero(gym, idCliente, generoCliente);

	printf("Genero: %s\n", generoCliente);
	printf("Clases: ");

	clasesSize = GymObtenerClienteClasesNombresIds(gym, idCliente, nombresClases, idsClases);

	if (clasesSize > 0)
	{
		for (int j = 0; j < clasesSize; j++)
		{
			printf("%s, ", nombresClases[j]);
		}

		printf("\b\b. \n");
	}
	else
	{
		printf("Sin clases asignadas.\n");
	}

	MontoTotal = GymObtenerClienteMontoTotalClases(gym, idCliente);

	printf("Monto a Abonar: $%.2f\n\n", MontoTotal);

	printf("\n--------------------------------------\n");
}

static void MenuMostrarClasesDelDia(Gym* gym)
{

}