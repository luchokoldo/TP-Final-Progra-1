#ifndef GYM_INCLUDED
#define GYM_INCLUDED

#include "entrenador.h"
#include "clase.h"
#include "sector.h"
#include "cliente.h"

typedef struct Gym
{
    Entrenador* entrenadores;
    int entrenadoresSize;
    Clase* clases;
    int clasesSize;
    Sector* sectores;
    int sectoresSize;
    Cliente* clientes;
    int clientesSize;
} Gym;

#endif // GYM_INCLUDED
