#ifndef _CLIENTE_H_INCLUDED
#define _CLIENTE_H_INCLUDED

#include "constgym.h"


typedef struct Cliente
{
    int id;
    char nombre[MAX_NOMBRE_TEXT];
    char genero[MAX_GENERO_TEXT];
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
void ClienteObtenerClientesNombresIds(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_TEXT], int* idsClientes);
void ClienteObtenerClienteClasesIds(Cliente* cliente, int* idsClases);
int ClienteObtenerCantidadClasesEnCliente(Cliente* cliente);

void ClienteModificarClienteNombre(Cliente* clientes, int size, int idCliente, char* nombreNuevo);
void ClienteModificarClienteGenero(Cliente* clientes, int size, int idCliente, char* generoNuevo);

void ClienteOrdenarClientes(Cliente* cliente, int size);

#endif
