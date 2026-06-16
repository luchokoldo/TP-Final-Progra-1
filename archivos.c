#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "constgym.h"
#include "archivos.h"

#define ARCHIVO_ENTRENADORES		"Entrenadores.bin"
#define ARCHIVO_SECTORES			"Sectores.bin"
#define ARCHIVO_CLASES				"Clases.bin"
#define ARCHIVO_CLIENTES			"Clientes.bin"
#define ARCHIVO_IDS					"Ids.bin"

#define ARCHIVO_ENTRENADORES_TXT	"Entrenadores"
#define ARCHIVO_SECTORES_TXT		"Sectores"
#define ARCHIVO_CLASES_TXT			"Clases"
#define ARCHIVO_CLIENTES_TXT		"Clientes"
#define ARCHIVO_NOMBRE_SIZE_TXT		64

static Entrenador* ArchivoCargarEntrenadores(char* nombreArchivo, int* size);
static Sector* ArchivoCargarSectores(char* nombreArchivo, int* size);
static Clase* ArchivoCargarClases(char* nombreArchivo, int* size);
static Cliente* ArchivoCargarClientes(char* nombreArchivo, int* size);
static GymIds ArchivoCargarIds(char* nombreArchivo);

static void ArchivoGuardarEntrenadores(char* nombreArchivo, Entrenador* entrenadores, int size);
static void ArchivoGuardarSectores(char* nombreArchivo, Sector* sectores, int size);
static void ArchivoGuardarClases(char* nombreArchivo, Clase* clases, int size);
static void ArchivoGuardarClientes(char* nombreArchivo, Cliente* clientes, int size);
static void ArchivoGuardarIds(char* nombreArchivo, GymIds* ids);
static void ArchivoBorrarArchivo(char* nombreArchivo);

void ArchivoGuardarGym(Gym* gym)
{
	if (gym->entrenadores != NULL)
	{
		ArchivoGuardarEntrenadores(ARCHIVO_ENTRENADORES, gym->entrenadores, gym->entrenadoresSize);
	}

	if (gym->sectores != NULL)
	{
		ArchivoGuardarSectores(ARCHIVO_SECTORES, gym->sectores, gym->sectoresSize);
	}
	
	if (gym->clases != NULL)
	{
		ArchivoGuardarClases(ARCHIVO_CLASES, gym->clases, gym->clasesSize);
	}
	
	if (gym->clientes != NULL)
	{
		ArchivoGuardarClientes(ARCHIVO_CLIENTES, gym->clientes, gym->clientesSize);
	}

	ArchivoGuardarIds(ARCHIVO_IDS, &gym->ids);
}

void ArchivoCargarGym(Gym* gym)
{
	gym->entrenadores = ArchivoCargarEntrenadores(ARCHIVO_ENTRENADORES, &gym->entrenadoresSize);
	gym->sectores = ArchivoCargarSectores(ARCHIVO_SECTORES, &gym->sectoresSize);
	gym->clases = ArchivoCargarClases(ARCHIVO_CLASES, &gym->clasesSize);
	gym->clientes = ArchivoCargarClientes(ARCHIVO_CLIENTES, &gym->clientesSize);
	gym->ids = ArchivoCargarIds(ARCHIVO_IDS);
}

void ArchivoAgregarEntrenador(Entrenador* entrenador)
{
	FILE* f = fopen(ARCHIVO_ENTRENADORES, "ab");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo agregar un elemento a %s\n", ARCHIVO_ENTRENADORES);

		return;
	}

	fwrite(entrenador, sizeof(Entrenador), 1, f);

	fclose(f);
}

void ArchivoAgregarSector(Sector* sector)
{
	FILE* f = fopen(ARCHIVO_SECTORES, "ab");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo agregar un elemento a %s\n", ARCHIVO_SECTORES);

		return;
	}

	fwrite(sector, sizeof(Sector), 1, f);

	fclose(f);
}

void ArchivoAgregarClase(Clase* clase)
{
	FILE* f = fopen(ARCHIVO_CLASES, "ab");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo agregar un elemento a %s\n", ARCHIVO_CLASES);

		return;
	}

	fwrite(clase, sizeof(Clase), 1, f);

	fclose(f);
}

void ArchivoAgregarCliente(Cliente* cliente)
{
	FILE* f = fopen(ARCHIVO_CLIENTES, "ab");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo agregar un elemento a %s\n", ARCHIVO_CLIENTES);

		return;
	}

	fwrite(cliente, sizeof(Cliente), 1, f);

	fclose(f);
}

void ArchivoModificarEntrenador(Entrenador* entrenador)
{
	FILE* f = fopen(ARCHIVO_ENTRENADORES, "r+b");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo abrir el archivo %s\n", ARCHIVO_ENTRENADORES);

		return;
	}

	Entrenador buffer = { 0 };

	do
	{
		if (fread(&buffer, sizeof(Entrenador), 1, f) <= 0)
		{
			printf("[ERROR] No se encontro el entrenador %s\n", entrenador->nombre);

			fclose(f);

			return;
		}
	} while (buffer.id != entrenador->id);

	fseek(f, -1 * sizeof(Entrenador), SEEK_CUR);

	fwrite(entrenador, sizeof(Entrenador), 1, f);

	fclose(f);
}

void ArchivoModificarSector(Sector* sector)
{
	FILE* f = fopen(ARCHIVO_SECTORES, "r+b");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo abrir el archivo %s\n", ARCHIVO_SECTORES);

		return;
	}

	Sector buffer = { 0 };

	do
	{
		if (fread(&buffer, sizeof(Sector), 1, f) <= 0)
		{
			printf("[ERROR] No se encontro el sector %s\n", sector->nombre);

			fclose(f);

			return;
		}
	} while (buffer.id != sector->id);

	fseek(f, -1 * sizeof(Sector), SEEK_CUR);

	fwrite(sector, sizeof(Sector), 1, f);

	fclose(f);
}

void ArchivoModificarClase(Clase* clase)
{
	FILE* f = fopen(ARCHIVO_CLASES, "r+b");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo abrir el archivo %s\n", ARCHIVO_CLASES);

		return;
	}

	Clase buffer = { 0 };

	do
	{
		if (fread(&buffer, sizeof(Clase), 1, f) <= 0)
		{
			printf("[ERROR] No se encontro la clase %s\n", clase->nombre);

			fclose(f);

			return;
		}
	} while (buffer.id != clase->id);

	fseek(f, -1 * sizeof(Clase), SEEK_CUR);

	fwrite(clase, sizeof(Clase), 1, f);

	fclose(f);
}

void ArchivoModificarCliente(Cliente* cliente)
{
	FILE* f = fopen(ARCHIVO_CLIENTES, "r+b");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo abrir el archivo %s\n", ARCHIVO_CLIENTES);

		return;
	}

	Cliente buffer = { 0 };

	do
	{
		if (fread(&buffer, sizeof(Cliente), 1, f) <= 0)
		{
			printf("[ERROR] No se encontro el cliente %s\n", cliente->nombre);

			fclose(f);

			return;
		}
	} while (buffer.id != cliente->id);

	fseek(f, -1 * sizeof(Cliente), SEEK_CUR);

	fwrite(cliente, sizeof(Cliente), 1, f);

	fclose(f);
}

void ArchivoBorrarEntrenador(int idEntrenador)
{
	FILE* f = fopen(ARCHIVO_ENTRENADORES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_ENTRENADORES);

		return;
	}

	Entrenador* aux = NULL;
	size_t size = 0;
	Entrenador buffer = { 0 };

	while (fread(&buffer, sizeof(Entrenador), 1, f) > 0)
	{
		if (buffer.id == idEntrenador)
		{
			continue;
		}
		
		Entrenador* temp = realloc(aux, (size + 1) * sizeof(Entrenador));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size + 1) * sizeof(Entrenador)) devolvio NULL\n");

			free(aux);

			fclose(f);

			return;
		}

		aux = temp;

		aux[size] = buffer;

		size++;
	}

	fclose(f);

	f = fopen(ARCHIVO_ENTRENADORES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_ENTRENADORES);

		free(aux);

		return;
	}

	if (size > 0)
	{
		fwrite(aux, sizeof(Entrenador), size, f);
	}

	fclose(f);

	free(aux);
}

void ArchivoBorrarSector(int idSector)
{
	FILE* f = fopen(ARCHIVO_SECTORES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_SECTORES);

		return;
	}

	Sector* aux = NULL;
	size_t size = 0;
	Sector buffer = { 0 };

	while (fread(&buffer, sizeof(Sector), 1, f) > 0)
	{
		if (buffer.id == idSector)
		{
			continue;
		}

		Sector* temp = realloc(aux, (size + 1) * sizeof(Sector));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size + 1) * sizeof(Sector)) devolvio NULL\n");

			free(aux);

			fclose(f);

			return;
		}

		aux = temp;

		aux[size] = buffer;

		size++;
	}

	fclose(f);

	f = fopen(ARCHIVO_SECTORES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_SECTORES);

		free(aux);

		return;
	}

	if (size > 0)
	{
		fwrite(aux, sizeof(Sector), size, f);
	}

	fclose(f);

	free(aux);
}

void ArchivoBorrarClase(int idClase)
{
	FILE* f = fopen(ARCHIVO_CLASES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_CLASES);

		return;
	}

	Clase* aux = NULL;
	size_t size = 0;
	Clase buffer = { 0 };

	while (fread(&buffer, sizeof(Clase), 1, f) > 0)
	{
		if (buffer.id == idClase)
		{
			continue;
		}

		Clase* temp = realloc(aux, (size + 1) * sizeof(Clase));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size + 1) * sizeof(Clase)) devolvio NULL\n");

			free(aux);

			fclose(f);

			return;
		}

		aux = temp;

		aux[size] = buffer;

		size++;
	}

	fclose(f);

	f = fopen(ARCHIVO_CLASES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_CLASES);

		free(aux);

		return;
	}

	if (size > 0)
	{
		fwrite(aux, sizeof(Clase), size, f);
	}

	fclose(f);

	free(aux);
}

void ArchivoBorrarCliente(int idCliente)
{
	FILE* f = fopen(ARCHIVO_CLIENTES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_CLIENTES);

		return;
	}

	Cliente* aux = NULL;
	size_t size = 0;
	Cliente buffer = { 0 };

	while (fread(&buffer, sizeof(Cliente), 1, f) > 0)
	{
		if (buffer.id == idCliente)
		{
			continue;
		}

		Cliente* temp = realloc(aux, (size + 1) * sizeof(Cliente));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size + 1) * sizeof(Cliente)) devolvio NULL\n");

			free(aux);

			fclose(f);

			return;
		}

		aux = temp;

		aux[size] = buffer;

		size++;
	}

	fclose(f);

	f = fopen(ARCHIVO_CLIENTES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_CLIENTES);

		free(aux);

		return;
	}

	if (size > 0)
	{
		fwrite(aux, sizeof(Cliente), size, f);
	}

	fclose(f);

	free(aux);
}

void ArchivoExportarEntrenadores(int entrenadoresSize, int* idsEntrenadores, char nombresEntrenadores[][MAX_NOMBRE_TEXT], char generosEntrenadores[][MAX_GENERO_TEXT])
{
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	char nombreArchivo[ARCHIVO_NOMBRE_SIZE_TXT];
	
	snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d.txt", ARCHIVO_ENTRENADORES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

	FILE* f = fopen(nombreArchivo, "r");

	if (f != NULL)
	{
		int i = 0;

		do
		{
			fclose(f);

			snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d_%d.txt", ARCHIVO_ENTRENADORES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, ++i);

			f = fopen(nombreArchivo, "r");
		} while (f != NULL);
	}

	f = fopen(nombreArchivo, "w");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fprintf(f, "\t%s\n", ARCHIVO_ENTRENADORES_TXT);

	fprintf(f, "\n--------------------------------------\n\n");

	for (int i = 0; i < entrenadoresSize; i++)
	{
		fprintf(f, "ID: %d\n", idsEntrenadores[i]);
		fprintf(f, "Nombre: %s\n", nombresEntrenadores[i]);
		fprintf(f, "Genero: %s\n\n", generosEntrenadores[i]);		
	}

	fprintf(f, "--------------------------------------\n");

	fclose(f);
}

void ArchivoExportarSectores(int sectoresSize, int* idsSectores, char nombresSectores[][MAX_NOMBRE_TEXT])
{
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	char nombreArchivo[ARCHIVO_NOMBRE_SIZE_TXT];

	snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d.txt", ARCHIVO_SECTORES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

	FILE* f = fopen(nombreArchivo, "r");

	if (f != NULL)
	{
		int i = 0;

		do
		{
			fclose(f);

			snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d_%d.txt", ARCHIVO_SECTORES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, ++i);

			f = fopen(nombreArchivo, "r");
		} while (f != NULL);
	}

	f = fopen(nombreArchivo, "w");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fprintf(f, "\t%s\n", ARCHIVO_SECTORES_TXT);

	fprintf(f, "\n--------------------------------------\n\n");

	for (int i = 0; i < sectoresSize; i++)
	{
		fprintf(f, "ID: %d\n", idsSectores[i]);
		fprintf(f, "Nombre: %s\n\n", nombresSectores[i]);
	}

	fprintf(f, "--------------------------------------\n");

	fclose(f);
}

void ArchivoExportarClases(int clasesSize, int* idsClases, char nombresClases[][MAX_NOMBRE_TEXT], char nombresEntrenadores[][MAX_NOMBRE_TEXT],
							char nombresSectores[][MAX_NOMBRE_TEXT], int idsClasesClientes[][MAX_IDS], int clientesSize, int* idsClientes, 
							char nombresClientes[][MAX_NOMBRE_TEXT], int* clasesClientesValidos, double* preciosClases, int* inicioHorasClases, 
							int* inicioMinutosClases, int* duracionHorasClases, int* duracionMinutosClases)
{
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	char nombreArchivo[ARCHIVO_NOMBRE_SIZE_TXT];

	snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d.txt", ARCHIVO_CLASES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

	FILE* f = fopen(nombreArchivo, "r");

	if (f != NULL)
	{
		int i = 0;

		do
		{
			fclose(f);

			snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d_%d.txt", ARCHIVO_CLASES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, ++i);

			f = fopen(nombreArchivo, "r");
		} while (f != NULL);
	}

	f = fopen(nombreArchivo, "w");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fprintf(f, "\t%s\n", ARCHIVO_CLASES_TXT);

	fprintf(f, "\n-------------------------------------\n\n");

	int index = 0;

	for (int i = 0; i < clasesSize; i++)
	{	
		fprintf(f, "Id de la clase: %d\n", idsClases[i]);
		fprintf(f, "Clase: %s\n", nombresClases[i]);
		fprintf(f, "Entrenador: %s\n", nombresEntrenadores[i]);
		fprintf(f, "Sector: %s\n", nombresSectores[i]);
		fprintf(f, "Clientes: ");

		if (clasesClientesValidos[i] > 0)
		{
			for (index = 0; index < clientesSize; index++)
			{
				if (idsClasesClientes[i][0] == idsClientes[index])
				{
					break;
				}
			}
			
			fprintf(f, "%s", nombresClientes[index]);
			
			for (int j = 1; j < clasesClientesValidos[i]; j++)
			{
				for (index = 0; index < clientesSize; index++)
				{
					if (idsClasesClientes[i][j] == idsClientes[index])
					{
						break;
					}
				}
				
				fprintf(f, ", %s", nombresClientes[index]);
			}

			fprintf(f, ".\n");
		}
		else
		{
			fprintf(f, "Sin clientes asignados.\n");
		}

		fprintf(f, "Precio: $%.2f\n", preciosClases[i]);
		fprintf(f, "Hora de inicio: %02d:%02d\n", inicioHorasClases[i], inicioMinutosClases[i]);
		fprintf(f, "Duracion: %02d:%02d\n\n", duracionHorasClases[i], duracionMinutosClases[i]);
	}

	fprintf(f, "--------------------------------------\n");

	fclose(f);
}

void ArchivoExportarClientes(int clientesSize, int* idsClientes, char nombresClientes[][MAX_NOMBRE_TEXT], char generosClientes[][MAX_GENERO_TEXT], int idsClientesClases[][MAX_IDS],
								int* clientesClasesValidos, double* montosTotalClases, int clasesSize, int* idsClases, char nombresClases[][MAX_NOMBRE_TEXT])
{
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	char nombreArchivo[ARCHIVO_NOMBRE_SIZE_TXT];

	snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d.txt", ARCHIVO_CLIENTES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

	FILE* f = fopen(nombreArchivo, "r");

	if (f != NULL)
	{
		int i = 0;

		do
		{
			fclose(f);

			snprintf(nombreArchivo, ARCHIVO_NOMBRE_SIZE_TXT, "%s_%02d%02d%04d_%d.txt", ARCHIVO_CLIENTES_TXT, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, ++i);

			f = fopen(nombreArchivo, "r");
		} while (f != NULL);
	}

	f = fopen(nombreArchivo, "w");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fprintf(f, "\t%s\n", ARCHIVO_CLIENTES_TXT);

	fprintf(f, "\n--------------------------------------\n\n");
	
	int index = 0;

	for (int i = 0; i < clientesSize; i++)
	{
		fprintf(f, "ID: %d\n", idsClientes[i]);
		fprintf(f, "Nombre: %s\n", nombresClientes[i]);
		fprintf(f, "Genero: %s\n", generosClientes[i]);
		fprintf(f, "Clases: ");
		
		if (clientesClasesValidos[i] > 0)
		{
			for (index = 0; index < clasesSize; index++)
			{
				if (idsClientesClases[i][0] == idsClases[index])
				{
					break;
				}
			}
			
			fprintf(f, "%s", nombresClases[index]);
			
			for (int j = 1; j < clientesClasesValidos[i]; j++)
			{
				for (index = 0; index < clasesSize; index++)
				{
					if (idsClientesClases[i][j] == idsClases[index])
					{
						break;
					}
				}
				
				fprintf(f, ", %s", nombresClases[index]);
			}

			fprintf(f, ".\n");
		}
		else
		{
			fprintf(f, "Sin clases asignadas.\n");
		}

		fprintf(f, "Monto a abonar: $%.2f\n\n", montosTotalClases[i]);
	}

	fprintf(f, "--------------------------------------\n");

	fclose(f);
}

void ArchivoBorrarEntrenadores()
{
	ArchivoBorrarArchivo(ARCHIVO_ENTRENADORES);
}

void ArchivoBorrarSectores()
{
	ArchivoBorrarArchivo(ARCHIVO_SECTORES);
}

void ArchivoBorrarClases()
{
	ArchivoBorrarArchivo(ARCHIVO_CLASES);
}

void ArchivoBorrarClientes()
{
	ArchivoBorrarArchivo(ARCHIVO_CLIENTES);
}

void ArchivoActualizarIds(GymIds* ids)
{
	ArchivoGuardarIds(ARCHIVO_IDS, ids);
}

static Entrenador* ArchivoCargarEntrenadores(char* nombreArchivo, int* size)
{
	*size = 0;

	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		return NULL;
	}

	Entrenador* aux = NULL;
	Entrenador buffer = { 0 };

	while (fread(&buffer, sizeof(Entrenador), 1, f) > 0)
	{
		
		Entrenador* temp = realloc(aux, (size_t)(*size + 1) * sizeof(Entrenador));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size_t)(*size + 1) * sizeof(Entrenador)) devolvio NULL\n");

			free(aux);

			fclose(f);

			*size = 0;

			return NULL;
		}

		aux = temp;

		aux[*size] = buffer;

		(*size)++;
	}

	fclose(f);

	return aux;
}

static Sector* ArchivoCargarSectores(char* nombreArchivo, int* size)
{
	*size = 0;

	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		return NULL;
	}

	Sector* aux = NULL;
	Sector buffer = { 0 };

	while (fread(&buffer, sizeof(Sector), 1, f) > 0)
	{

		Sector* temp = realloc(aux, (size_t)(*size + 1) * sizeof(Sector));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size_t)(*size + 1) * sizeof(Sector)) devolvio NULL\n");

			free(aux);

			fclose(f);

			*size = 0;

			return NULL;
		}

		aux = temp;

		aux[*size] = buffer;

		(*size)++;
	}

	fclose(f);

	return aux;
}

static Clase* ArchivoCargarClases(char* nombreArchivo, int* size)
{
	*size = 0;

	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		return NULL;
	}

	Clase* aux = NULL;
	Clase buffer = { 0 };

	while (fread(&buffer, sizeof(Clase), 1, f) > 0)
	{

		Clase* temp = realloc(aux, (size_t)(*size + 1) * sizeof(Clase));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size_t)(*size + 1) * sizeof(Clase)) devolvio NULL\n");

			free(aux);

			fclose(f);

			*size = 0;

			return NULL;
		}

		aux = temp;

		aux[*size] = buffer;

		(*size)++;
	}

	fclose(f);

	return aux;
}

static Cliente* ArchivoCargarClientes(char* nombreArchivo, int* size)
{
	*size = 0;

	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		return NULL;
	}

	Cliente* aux = NULL;
	Cliente buffer = { 0 };

	while (fread(&buffer, sizeof(Cliente), 1, f) > 0)
	{

		Cliente* temp = realloc(aux, (size_t)(*size + 1) * sizeof(Cliente));

		if (temp == NULL)
		{
			printf("[ERROR] realloc(aux, (size_t)(*size + 1) * sizeof(Cliente)) devolvio NULL\n");

			free(aux);

			fclose(f);

			*size = 0;

			return NULL;
		}

		aux = temp;

		aux[*size] = buffer;

		(*size)++;
	}

	fclose(f);

	return aux;
}

static GymIds ArchivoCargarIds(char* nombreArchivo)
{
	FILE* f = fopen(nombreArchivo, "rb");

	GymIds ids = { 0 };

	if (f == NULL)
	{
		return ids;
	}

	fread(&ids, sizeof(GymIds), 1, f);

	return ids;
}

static void ArchivoGuardarEntrenadores(char* nombreArchivo, Entrenador* entrenadores, int size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fwrite(entrenadores, sizeof(Entrenador), (size_t)size, f);

	fclose(f);
}

static void ArchivoGuardarSectores(char* nombreArchivo, Sector* sectores, int size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fwrite(sectores, sizeof(Sector), (size_t)size, f);

	fclose(f);
}

static void ArchivoGuardarClases(char* nombreArchivo, Clase* clases, int size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fwrite(clases, sizeof(Clase), (size_t)size, f);

	fclose(f);
}

static void ArchivoGuardarClientes(char* nombreArchivo, Cliente* clientes, int size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fwrite(clientes, sizeof(Cliente), (size_t)size, f);

	fclose(f);
}

static void ArchivoGuardarIds(char* nombreArchivo, GymIds* ids)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fwrite(ids, sizeof(GymIds), 1, f);

	fclose(f);
}

static void ArchivoBorrarArchivo(char* nombreArchivo)
{
	if (remove(nombreArchivo) != 0)
	{
		printf("[ERROR] No se pudo borrar el archivo %s", nombreArchivo);
	}
}