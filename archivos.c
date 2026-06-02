#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"

#define ARCHIVO_ENTRENADORES	"Entrenadores.bin"
#define ARCHIVO_SECTORES	"Sectores.bin"
#define ARCHIVO_CLASES		"Clases.bin"
#define ARCHIVO_CLIENTES	"Clientes.bin"

static Entrenador* CargarEntrenadores(char* nombreArchivo, int* size);
static Sector* CargarSectores(char* nombreArchivo, int* size);
static Clase* CargarClases(char* nombreArchivo, int* size);
static Cliente* CargarClientes(char* nombreArchivo, int* size);
static void GuardarEntrenadores(char* nombreArchivo, Entrenador* entrenadores, int* size);
static void GuardarSectores(char* nombreArchivo, Sector* sectores, int* size);
static void GuardarClases(char* nombreArchivo, Clase* clases, int* size);
static void GuardarClientes(char* nombreArchivo, Cliente* clientes, int* size);

void GuardarGym(Gym* gym)
{
	GuardarEntrenadores(ARCHIVO_ENTRENADORES, gym->entrenadores, gym->entrenadoresSize);
	GuardarSectores(ARCHIVO_SECTORES, gym->sectores, gym->entrenadoresSize);
	GuardarClases(ARCHIVO_CLASES, gym->clases, gym->entrenadoresSize);
	GuardarClientes(ARCHIVO_CLIENTES, gym->clientes, gym->entrenadoresSize);
}

void CargarGym(Gym* gym)
{
	gym->entrenadores = CargarEntrenadores(ARCHIVO_ENTRENADORES, &gym->entrenadoresSize);
	gym->sectores = CargarSectores(ARCHIVO_SECTORES, &gym->sectoresSize);
	gym->clases = CargarClases(ARCHIVO_CLASES, &gym->clasesSize);
	gym->clientes = CargarClientes(ARCHIVO_CLIENTES, &gym->clientesSize);
}

void ModificarEntrenador(Entrenador* entrenador)
{

}

void ModificarSector(Sector* sector)
{

}

void ModificarClase(Clase* clase)
{

}

void ModificarCliente(Cliente* cliente)
{

}

void BorrarEntrenador(Entrenador* entrenador)
{

}

void BorrarSector(Sector* sector)
{

}

void BorrarClase(Clase* clase)
{

}

void BorrarCliente(Cliente* cliente)
{

}

static Entrenador* CargarEntrenadores(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Entrenador* aux = calloc(1, sizeof(Entrenador));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Entrenador)) devolvio NULL");

			return NULL;
		}

		return aux;
	}

	Entrenador* aux = calloc(1, sizeof(Entrenador));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Entrenador)) devolvio NULL");

		return NULL;
	}

	Entrenador buffer = { 0 };

	while (fread(&buffer, sizeof(Entrenador), 1, f) > 0)
	{
		aux[*size] = buffer;

		(*size)++;

		if (feof(f) == 0)
		{
			aux = realloc(&aux, (*size + 1) * sizeof(Entrenador));

			if (aux == NULL)
			{
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Entrenador)) devolvio NULL");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static Sector* CargarSectores(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Sector* aux = calloc(1, sizeof(Sector));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Sector)) devolvio NULL");

			return NULL;
		}

		return aux;
	}

	Sector* aux = calloc(1, sizeof(Sector));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Sector)) devolvio NULL");

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
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Sector)) devolvio NULL");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static Clase* CargarClases(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Clase* aux = calloc(1, sizeof(Clase));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Clase)) devolvio NULL");

			return NULL;
		}

		return aux;
	}

	Clase* aux = calloc(1, sizeof(Clase));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Clase)) devolvio NULL");

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
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Clase)) devolvio NULL");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static Cliente* CargarClientes(char* nombreArchivo, int* size)
{
	FILE* f = fopen(nombreArchivo, "rb");

	if (f == NULL)
	{
		Cliente* aux = calloc(1, sizeof(Cliente));

		if (aux == NULL)
		{
			printf("[ERROR] calloc(1, sizeof(Cliente)) devolvio NULL");

			return NULL;
		}

		return aux;
	}

	Cliente* aux = calloc(1, sizeof(Cliente));

	if (aux == NULL)
	{
		printf("[ERROR] calloc(1, sizeof(Cliente)) devolvio NULL");

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
				printf("[ERROR] realloc(&aux, (*size + 1) * sizeof(Cliente)) devolvio NULL");

				*size = 0;

				return NULL;
			}
		}
	}

	fclose(f);

	return aux;
}

static void GuardarEntrenadores(char* nombreArchivo, Entrenador* entrenadores, int* size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s", nombreArchivo);

		return;
	}

	fwrite(&entrenadores, sizeof(Entrenador), (size_t)(*size), f);

	fclose(f);
}

static void GuardarSectores(char* nombreArchivo, Sector* sectores, int* size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s", nombreArchivo);

		return;
	}

	fwrite(&sectores, sizeof(Sector), (size_t)(*size), f);

	fclose(f);
}

static void GuardarClases(char* nombreArchivo, Clase* clases, int* size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s", nombreArchivo);

		return;
	}

	fwrite(&clases, sizeof(Clase), (size_t)(*size), f);

	fclose(f);
}

static void GuardarClientes(char* nombreArchivo, Cliente* clientes, int* size)
{
	FILE* f = fopen(nombreArchivo, "wb");

	if (f == NULL)
	{
		printf("[ERROR] No se pudro crear el archivo %s", nombreArchivo);

		return;
	}

	fwrite(&clientes, sizeof(Cliente), (size_t)(*size), f);

	fclose(f);
}

