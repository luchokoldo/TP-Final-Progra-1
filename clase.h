#ifndef _CLASE_H_INCLUDED
#define _CLASE_H_INCLUDED

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
    int idEntrenador;
    int idSector;
    int idClientes[32];
    int idClientesValidos;
    double precio;
    Horario inicio;
    Duracion duracion;
} Clase;

#endif