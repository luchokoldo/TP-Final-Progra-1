#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"


static void limpiarBuferDeEntrada(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int ScannerConfirmar(char condicion)
{
	char aux = '\0';
	scanf("%c", &aux);
	limpiarBuferDeEntrada();
	return tolower(aux) == tolower(condicion);
}

int ScannerInt(void)
{
	int aux = 0;
	scanf("%d", &aux);
	limpiarBuferDeEntrada();
	return aux;
}

float ScannerFloat(void)
{
	float aux = 0;
	scanf("%f", &aux);
	limpiarBuferDeEntrada();
	return aux;
}

double ScannerDouble(void)
{
	double aux = 0;
	scanf("%lf", &aux);
	limpiarBuferDeEntrada();
	return aux;
}

int ScannerString(char* string, int maxLength)
{
	if (fgets(string, maxLength, stdin) == NULL)
	{
		return -1;
	}

	int ult = strlen(string) - 1;

	if (string[ult] == '\n')
	{
		string[ult] = '\0';
	}
	else
	{
		limpiarBuferDeEntrada();
	}

	return strlen(string);
}