#ifndef _UTILIDADES_H_INCLUDED
#define _UTILIDADES_H_INCLUDED

#define GET_CHARSMAX(arreglo)	sizeof(arreglo) / sizeof(arreglo[0])
#define COMPARAR_HORARIO(horas1, minutos1, horas2, minutos2)	(horas1 * 60 + minutos1) - (horas2 * 60 + minutos2) // > 0 (1) empieza mas tarde, < 0 (2) empieza mas tarde

char* UtilidadesStringTrim(char* str);

#endif
