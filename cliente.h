#ifndef _CLIENTE_H_INCLUDED
#define _CLIENTE_H_INCLUDED

typedef struct Cliente
{
    int id;
    char nombre[64];
    char genero[32];
    int idClases[32];
    int idClasesValidos;
} Cliente;
void ClienteMostrarCliente(Cliente* clientes, int size);
Cliente* ClienteAgregarCliente(Cliente* clientes, int* size);
int ClienteBuscarClienteId(Cliente* cliente, int size, int id, int i);
void ClienteModificarCliente(Cliente* cliente, int size, int id);
Cliente* ClienteEliminarCliente(Cliente* clientes, int* size, int id);
void ClienteExportarTxt(Cliente* clientes, int size);
#endif
