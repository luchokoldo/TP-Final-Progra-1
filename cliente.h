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

#endif
