#ifndef _CLIENTE_H_INCLUDED
#define _CLIENTE_H_INCLUDED

#define MAX_NOMBRE_CLIENTE_SIZE 64
#define MAX_GENERO_CLIENTE_SIZE 32
#define MAX_ID_CLIENTE_SIZE 32
#define CLIENTE_ID_INVALIDO      -1


typedef struct Cliente
{
    int id;
    char nombre[MAX_NOMBRE_CLIENTE_SIZE];
    char genero[MAX_GENERO_CLIENTE_SIZE];
    int idClases[MAX_ID_CLIENTE_SIZE];
    int idClasesValidos;
} Cliente;

Cliente* ClienteAgregarCliente(Cliente* clientes, int size, int id,char *nombre, char *genero);
void ClienteMostrarCliente(Cliente* clientes, int size);
int ClienteBuscarId(Cliente* cliente, int size, int id, int i);
void ClienteModificarCliente(Cliente* cliente, int size, int id);
Cliente* ClienteEliminarCliente(Cliente* clientes, int* size, int id);
void ClienteExportarTxt(Cliente* clientes, int size);

#endif
