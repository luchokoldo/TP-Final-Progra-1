#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"

#define ARCHIVO_ENTRENADORES	"Entrenadores.bin"
#define ARCHIVO_SECTORES	"Sectores.bin"
#define ARCHIVO_CLASES		"Clases.bin"
#define ARCHIVO_CLIENTES	"Clientes.bin"

static Entrenador* ArchivoCargarEntrenadores(char* nombreArchivo, int* size);
static Sector* ArchivoCargarSectores(char* nombreArchivo, int* size);
static Clase* ArchivoCargarClases(char* nombreArchivo, int* size);
static Cliente* ArchivoCargarClientes(char* nombreArchivo, int* size);

static void ArchivoGuardarEntrenadores(char* nombreArchivo, Entrenador* entrenadores, int size);
static void ArchivoGuardarSectores(char* nombreArchivo, Sector* sectores, int size);
static void ArchivoGuardarClases(char* nombreArchivo, Clase* clases, int size);
static void ArchivoGuardarClientes(char* nombreArchivo, Cliente* clientes, int size);

void ArchivoGuardarGym(Gym* gym)
{
	ArchivoGuardarEntrenadores(ARCHIVO_ENTRENADORES, gym->entrenadores, gym->entrenadoresSize);
	ArchivoGuardarSectores(ARCHIVO_SECTORES, gym->sectores, gym->entrenadoresSize);
	ArchivoGuardarClases(ARCHIVO_CLASES, gym->clases, gym->entrenadoresSize);
	ArchivoGuardarClientes(ARCHIVO_CLIENTES, gym->clientes, gym->entrenadoresSize);
}

void ArchivoCargarGym(Gym* gym)
{
	gym->entrenadores = ArchivoCargarEntrenadores(ARCHIVO_ENTRENADORES, &gym->entrenadoresSize);
	gym->sectores = ArchivoCargarSectores(ARCHIVO_SECTORES, &gym->sectoresSize);
	gym->clases = ArchivoCargarClases(ARCHIVO_CLASES, &gym->clasesSize);
	gym->clientes = ArchivoCargarClientes(ARCHIVO_CLIENTES, &gym->clientesSize);
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

			return;
		}
	} while (buffer.id != cliente->id);

	fseek(f, -1 * sizeof(Cliente), SEEK_CUR);

	fwrite(cliente, sizeof(Cliente), 1, f);

	fclose(f);
}

void ArchivoBorrarEntrenador(Entrenador* entrenador)
{
	FILE* f = fopen(ARCHIVO_ENTRENADORES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_ENTRENADORES);

		return;
	}

	Entrenador* aux = calloc(1, sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Entrenador)) devolvio NULL\n");

		return;
	}

	size_t size = 1;

	Entrenador buffer = { 0 };

	while (fread(&buffer, sizeof(Entrenador), 1, f) > 0)
	{
		if (buffer.id == entrenador->id)
		{
			continue;
		}

		aux[size - 1] = buffer;

		if (feof(f) == 0)
		{
			realloc(&aux, ++size * sizeof(Entrenador));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, ++size * sizeof(Entrenador)) devolvio NULL\n");

				return;
			}
		}
	}

	fclose(f);

	f = fopen(ARCHIVO_ENTRENADORES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_ENTRENADORES);

		return;
	}

	fwrite(aux, sizeof(Entrenador), size, f);

	fclose(f);
}

void ArchivoBorrarSector(Sector* sector)
{
	FILE* f = fopen(ARCHIVO_SECTORES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_SECTORES);

		return;
	}

	Sector* aux = calloc(1, sizeof(Sector));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Sector)) devolvio NULL\n");

		return;
	}

	size_t size = 1;

	Sector buffer = { 0 };

	while (fread(&buffer, sizeof(Sector), 1, f) > 0)
	{
		if (buffer.id == sector->id)
		{
			continue;
		}

		aux[size - 1] = buffer;

		if (feof(f) == 0)
		{
			realloc(&aux, ++size * sizeof(Sector));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, ++size * sizeof(Sector)) devolvio NULL\n");

				return;
			}
		}
	}

	fclose(f);

	f = fopen(ARCHIVO_SECTORES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_SECTORES);

		return;
	}

	fwrite(aux, sizeof(Sector), size, f);

	fclose(f);
}

void ArchivoBorrarClase(Clase* clase)
{
	FILE* f = fopen(ARCHIVO_CLASES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_CLASES);

		return;
	}

	Clase* aux = calloc(1, sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Clase)) devolvio NULL\n");

		return;
	}

	size_t size = 1;

	Clase buffer = { 0 };

	while (fread(&buffer, sizeof(Clase), 1, f) > 0)
	{
		if (buffer.id == clase->id)
		{
			continue;
		}

		aux[size - 1] = buffer;

		if (feof(f) == 0)
		{
			realloc(&aux, ++size * sizeof(Clase));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, ++size * sizeof(Clase)) devolvio NULL\n");

				return;
			}
		}
	}

	fclose(f);

	f = fopen(ARCHIVO_CLASES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_CLASES);

		return;
	}

	fwrite(aux, sizeof(Clase), size, f);

	fclose(f);
}

void ArchivoBorrarCliente(Cliente* cliente)
{
	FILE* f = fopen(ARCHIVO_CLIENTES, "rb");

	if (f == NULL)
	{
		printf("[ERROR] No se encontro el archivo %s\n", ARCHIVO_CLIENTES);

		return;
	}

	Cliente* aux = calloc(1, sizeof(Cliente));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Cliente)) devolvio NULL\n");

		return;
	}

	size_t size = 1;

	Cliente buffer = { 0 };

	while (fread(&buffer, sizeof(Cliente), 1, f) > 0)
	{
		if (buffer.id == cliente->id)
		{
			continue;
		}

		aux[size - 1] = buffer;

		if (feof(f) == 0)
		{
			realloc(&aux, ++size * sizeof(Cliente));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, ++size * sizeof(Cliente)) devolvio NULL\n");

				return;
			}
		}
	}

	fclose(f);

	f = fopen(ARCHIVO_CLIENTES, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudo crear el archivo %s\n", ARCHIVO_CLIENTES);

		return;
	}

	fwrite(aux, sizeof(Cliente), size, f);

	fclose(f);
}

static Entrenador* ArchivoCargarEntrenadores(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Entrenador* aux = calloc(1, sizeof(Entrenador));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Entrenador)) devolvio NULL\n");

			return NULL;
		}

		return aux;
	}

	Entrenador* aux = calloc(1, sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Entrenador)) devolvio NULL\n");

		return NULL;
	}

	Entrenador buffer = { 0 };

	while (fread(&buffer, sizeof(Entrenador), 1, f) > 0)
	{
		aux[*size] = buffer;

		(*size)++;

		if (feof(f) == 0)
		{
			realloc(&aux, (*size + 1) * sizeof(Entrenador));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Entrenador)) devolvio NULL\n");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static Sector* ArchivoCargarSectores(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Sector* aux = calloc(1, sizeof(Sector));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Sector)) devolvio NULL\n");

			return NULL;
		}

		return aux;
	}

	Sector* aux = calloc(1, sizeof(Sector));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Sector)) devolvio NULL\n");

		return NULL;
	}

	Sector buffer = { 0 };

	while (fread(&buffer, sizeof(Sector), 1, f) > 0)
	{
		aux[*size] = buffer;

		(*size)++;

		if (feof(f) == 0)
		{
			realloc(&aux, (*size + 1) * sizeof(Sector));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Sector)) devolvio NULL\n");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static Clase* ArchivoCargarClases(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Clase* aux = calloc(1, sizeof(Clase));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Clase)) devolvio NULL\n");

			return NULL;
		}

		return aux;
	}

	Clase* aux = calloc(1, sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Clase)) devolvio NULL\n");

		return NULL;
	}

	Clase buffer = { 0 };

	while (fread(&buffer, sizeof(Clase), 1, f) > 0)
	{
		aux[*size] = buffer;

		(*size)++;

		if (feof(f) == 0)
		{
			realloc(&aux, (*size + 1) * sizeof(Clase));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Clase)) devolvio NULL\n");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static Cliente* ArchivoCargarClientes(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Cliente* aux = calloc(1, sizeof(Cliente));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Cliente)) devolvio NULL\n");

			return NULL;
		}

		return aux;
	}

	Cliente* aux = calloc(1, sizeof(Cliente));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Cliente)) devolvio NULL\n");

		return NULL;
	}

	Cliente buffer = { 0 };

	while (fread(&buffer, sizeof(Cliente), 1, f) > 0)
	{
		aux[*size] = buffer;

		(*size)++;

		if (feof(f) == 0)
		{
			realloc(&aux, (*size + 1) * sizeof(Cliente));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Cliente)) devolvio NULL\n");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static void ArchivoGuardarEntrenadores(char* nombreArchivo, Entrenador* entrenadores, int size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s\n", nombreArchivo);

		return;
	}

	fwrite(&entrenadores, sizeof(Entrenador), (size_t)size, f);

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

	fwrite(&sectores, sizeof(Sector), (size_t)size, f);

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

	fwrite(&clases, sizeof(Clase), (size_t)size, f);

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

	fwrite(&clientes, sizeof(Cliente), (size_t)size, f);

	fclose(f);
}