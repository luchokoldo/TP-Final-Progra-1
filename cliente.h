#ifndef _CLIENTE_H_INCLUDED
#define _CLIENTE_H_INCLUDED

#define MAX_NOMBRE_CLIENTE_SIZE 64
#define MAX_GENERO_CLIENTE_SIZE 32
#define MAX_ID_CLASE_SIZE     32
#define CLIENTE_ID_INVALIDO     -1


typedef struct Cliente
{
    int id;
    char nombre[MAX_NOMBRE_CLIENTE_SIZE];
    char genero[MAX_GENERO_CLIENTE_SIZE];
    int idClases[MAX_ID_CLASE_SIZE];
    int idClasesValidos;
} Cliente;

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int idCliente, char *nombre, char *genero);
void ClienteMostrarClientes(Cliente* clientes, int size);
void ClienteMostrarCliente(Cliente* cliente);
int ClienteBuscarClienteId(Cliente* clientes, int size, int idCliente);
Cliente* ClienteEliminarCliente(Cliente* clientes, int size, int idCliente);

void ClienteAgregarClase(Cliente* cliente, int idClase);
void ClienteEliminarClase(Cliente* cliente, int idClase);

Cliente* ClienteObtenerCliente(Cliente* clientes, int size, int idCliente);
void ClienteObtenerClienteNombre(Cliente* clientes, int size, int idCliente, char* nombre);
void ClienteObtenerClienteGenero(Cliente* clientes, int size, int idCliente, char* genero);
void ClienteObtenerClientesNombresIds(Cliente* clientes, int size, char nombresClientes[][MAX_NOMBRE_CLIENTE_SIZE], int* idsClientes);
void ClienteObtenerClienteClasesIds(Cliente* cliente, int* idsClases);
int ClienteObtenerClasesEnCliente(Cliente* cliente);

void ClienteModificarClienteNombre(Cliente* clientes, int size, int idCliente, char* nombreNuevo);
void ClienteModificarClienteGenero(Cliente* clientes, int size, int idCliente, char* generoNuevo);

#endif
