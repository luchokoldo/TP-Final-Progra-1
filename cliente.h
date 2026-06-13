#ifndef _CLIENTE_H_INCLUDED
#define _CLIENTE_H_INCLUDED

#define MAX_NOMBRE_CLIENTE_SIZE 64
#define MAX_GENERO_CLIENTE_SIZE 32
#define MAX_ID_CLIENTE_SIZE     32
#define CLIENTE_ID_INVALIDO     -1


typedef struct Cliente
{
    int id;
    char nombre[MAX_NOMBRE_CLIENTE_SIZE];
    char genero[MAX_GENERO_CLIENTE_SIZE];
    int idClases[MAX_ID_CLIENTE_SIZE];
    int idClasesValidos;
} Cliente;

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int id, char *nombre, char *genero);
void ClienteMostrarClientes(Cliente* clientes, int size);
void ClienteMostrarCliente(Cliente* cliente);
int ClienteBuscarClienteId(Cliente* cliente, int size, int id);
Cliente* ClienteEliminarCliente(Cliente* clientes, int* size, int id);

void ClienteAgregarClase(Cliente* cliente, int idClase);
void ClienteElimarClase(Cliente* cliente, int idClase);

Cliente* ClienteObtenerCliente(Cliente* clientes, int size, int id);
void ClienteObtenerClienteNombre(Cliente* clientes, int size, int id, char* nombre);
void ClienteObtenerClienteGenero(Cliente* clientes, int size, int id, char* genero);
void ClienteObtenerClientesNombresIds(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);

void ClienteModificarClienteNombre(Cliente* clientes, int size, int id, char* nombreNuevo);
void ClienteModificarClienteGenero(Cliente* clientes, int size, int id, char* generoNuevo);

#endif
