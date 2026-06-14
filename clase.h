#ifndef _CLASE_H_INCLUDED
#define _CLASE_H_INCLUDED

#define MAX_NOMBRE_CLASE_SIZE   64
#define MAX_ID_CLIENTE_SIZE     32
#define CLASE_ID_INVALIDO       -1

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
    char nombre[MAX_NOMBRE_CLASE_SIZE];
    int idEntrenador;
    int idSector;
    int idClientes[MAX_ID_CLIENTE_SIZE];
    int idClientesValidos;
    double precio;
    Horario inicio;
    Duracion duracion;
} Clase;

Clase* ClaseAgregarClase(Clase* clases, int size, int id, char* nombre, double precio, Horario inicio, Duracion duracion);
void ClaseMostrarClases(Clase* clases, int size);
void ClaseMostrarClase(Clase* clase);
int ClaseBuscarClaseId(Clase* clase, int size, int id);
Clase* ClaseEliminarClase(Clase* clases, int* size, int id);

Clase* ClaseObtenerClase(Clase* clases, int size, int id);
void ClaseObtenerClaseNombre(Clase* clases, int size, int id, char* nombre);

void ClaseObtenerClasesNombresIds(Clase* clases, int size, char nombresClases[][MAX_NOMBRE_CLASE_SIZE], int* idsClases);
void ClaseModificarClaseNombre(Clase* clases, int size, int id, char* nombreNuevo);

void ClaseObtenerClaseHorario(Clase* clases, int size, int id, Horario* horario);
void ClaseModificarClaseHorario(Clase* clases, int size, int id, Horario horarioNuevo);

void ClaseObtenerClaseDuracion(Clase* clases, int size, int id, Duracion* duracion);
void ClaseModificarClaseDuracion(Clase* clases, int size, int id, Duracion duracionNueva);

void ClaseAgregarCliente(Clase* clase, int idCliente);
void ClaseEliminarCliente(Clase* clase, int idCliente);

void ClaseAsignarEntrenador(Clase* clase, int idEntrenador);
void ClaseEliminarEntrenador(Clase* clase);

void ClaseAsignarSector(Clase* clase, int idSector);
void ClaseEliminarSector(Clase* clase);


double ClaseObtenerClasePrecio(Clase* clases, int size, int id);
void ClaseEliminarPrecio(Clase* clases, int size, int id);
void ClaseAsignarPrecio(Clase* clases, int size, int id, double precioNuevo);

#endif