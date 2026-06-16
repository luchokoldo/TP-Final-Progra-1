#ifndef _CLASE_H_INCLUDED
#define _CLASE_H_INCLUDED

#include "constgym.h"

typedef struct Horario
{
    int horas;
    int minutos;
    int esValido;
} Horario;

typedef struct Duracion
{
    int horas;
    int minutos;
    int esValido;
} Duracion;

typedef struct Clase
{
    int id;
    char nombre[MAX_NOMBRE_SIZE];
    int idEntrenador;
    int idSector;
    int idClientes[MAX_IDS];
    int idClientesValidos;
    double precio;
    Horario inicio;
    Duracion duracion;
} Clase;

Clase* ClaseAgregarClase(Clase* clases, int size, int idClase, char* nombre, int idEntrenador, int idSector, double precio, Horario inicio, Duracion duracion);

int ClaseBuscarClaseId(Clase* clases, int size, int idClase);
int ClaseBuscarClaseEntrenadorId(Clase* clases, int size, int idEntrenador);
int ClaseBuscarClaseSectorId(Clase* clases, int size, int idSector);

Clase* ClaseObtenerClase(Clase* clases, int size, int idClase);
int ClaseObtenerCantidadClientesEnClase(Clase* clase);
void ClaseObtenerClaseNombre(Clase* clase, char* nombreClase);
void ClaseObtenerClaseClientesIds(Clase* clase, int* idsClientes);
int ClaseObtenerClaseEntrenador(Clase* clase);
int ClaseObtenerClaseSector(Clase* clase);
Horario ClaseObtenerClaseHorario(Clase* clase);
void ClaseObtenerClaseHorarioInt(Clase* clase, int* horasHorario, int* minutosHorario);
Duracion ClaseObtenerClaseDuracion(Clase* clase);
void ClaseObtenerClaseDuracionInt(Clase* clase, int* horasDuracion, int* minutosDuracion);
double ClaseObtenerClasePrecio(Clase* clase);
void ClaseObtenerClasesNombresIds(Clase* clases, int size, char nombresClases[][MAX_NOMBRE_SIZE], int* idsClases);
void ClaseObtenerClasesIds(Clase* clases, int size, int* idsClases);
void ClaseObtenerClasesNombres(Clase* clases, int size, char nombresClases[][MAX_NOMBRE_SIZE]);
void ClaseObtenerClasesEntrenadores(Clase* clases, int size, int* idsClasesEntrenadores);
void ClaseObtenerClasesSectores(Clase* clases, int size, int* idsClasesSectores);
void ClaseObtenerClasesClientes(Clase* clases, int size, int idsClasesClientes[][MAX_IDS], int* clasesClientesValidos);
void ClaseObtenerClasesPrecios(Clase* clases, int size, double* preciosClases);
void ClaseObtenerClasesHorarios(Clase* clases, int size, int* clasesHorariosHoras, int* clasesHorariosMinutos);
void ClaseObtenerClasesDuracion(Clase* clases, int size, int* clasesDuracionHoras, int* clasesDuracionMinutos);

void ClaseModificarClaseNombre(Clase* clases, int size, int idClase, char* nombreNuevo);
void ClaseModificarClaseHorario(Clase* clase, Horario horarioNuevo);
void ClaseModificarClaseDuracion(Clase* clase, Duracion duracionNueva);

int ClaseAgregarCliente(Clase* clase, int idCliente);
void ClaseAsignarEntrenador(Clase* clase, int idEntrenador);
void ClaseAsignarSector(Clase* clase, int idSector);
void ClaseAsignarPrecio(Clase* clase, double precioNuevo);

Clase* ClaseEliminarClase(Clase* clases, int size, int idClase);
void ClaseEliminarEntrenador(Clase* clase);
void ClaseEliminarSector(Clase* clase);
void ClaseEliminarCliente(Clase* clase, int idCliente);

int ClaseChequearClaseHorarioDuracion(Clase* clases, int size, int idClase, int idEntrenador, int idSector, Horario horario, Duracion duracion);

void ClaseOrdenarClases(Clase* clases, int size);

#endif