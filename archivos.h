#ifndef _ARCHIVOS_INCLUDED
#define _ARCHIVOS_INCLUDED

#include "gym.h"

void GuardarGym(Gym* gym);
void CargarGym(Gym* gym);

void ModificarEntrenador(Entrenador* entrenador);
void ModificarSector(Sector* sector);
void ModificarClase(Clase* clase);
void ModificarCliente(Cliente* cliente);

void BorrarEntrenador(Entrenador* entrenador);
void BorrarSector(Sector* sector);
void BorrarClase(Clase* clase);
void BorrarCliente(Cliente* cliente);

#endif
