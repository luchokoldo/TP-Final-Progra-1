#ifndef _CLIENTE_H_INCLUDED
#define _CLIENTE_H_INCLUDED

#include "constgym.h"

typedef struct Cliente
{
    int id;
    char nombre[MAX_NOMBRE_SIZE];
    char genero[MAX_GENERO_SIZE];
    int idClases[MAX_IDS];
    int idClasesValidos;
} Cliente;

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int idCliente, char *nombre, char *genero);
int ClienteBuscarClienteId(Cliente* clientes, int size, int idCliente);
Cliente* ClienteEliminarCliente(Cliente* clientes, int size, int idCliente);

int ClienteAgregarClase(Cliente* cliente, int idClase);
void ClienteEliminarClase(Cliente* cliente, int idClase);

Cliente* ClienteObtenerCliente(Cliente* clientes, int size, int idCliente);
void ClienteObtenerClienteNombre(Cliente* cliente, char* nombreCliente);
void ClienteObtenerClienteGenero(Cliente* cliente, char* generoCliente);
void ClienteObtenerClienteClasesIds(Cliente* cliente, int* idsClases);
void ClienteObtenerClientesNombresIds(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_SIZE], int* idsClientes);
void ClienteObtenerClientesIds(Cliente* clientes, int size, int* idsClientes);
void ClienteObtenerClientesNombres(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_SIZE]);
void ClienteObtenerClientesGeneros(Cliente* clientes, int size, char generosClientes[][MAX_GENERO_SIZE]);
void ClienteObtenerClientesClases(Cliente* clientes, int size, int idsClientesClases[][MAX_IDS], int* clientesClasesValidos);
int ClienteObtenerCantidadClasesEnCliente(Cliente* cliente);

void ClienteModificarClienteNombre(Cliente* clientes, int size, int idCliente, char* nombreNuevo);
void ClienteModificarClienteGenero(Cliente* clientes, int size, int idCliente, char* generoNuevo);

void ClienteOrdenarClientes(Cliente* cliente, int size);

#endif
