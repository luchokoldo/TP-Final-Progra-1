#include <stdio.h>
#include <stdlib.h>

#include "gym.h"
#include "archivos.h"
#include "menu.h"
int main()
{
	Gym gym = { 0 };


	CargarGym(&gym);

	MostrarMenu(&gym);

	GuardarGym(&gym);

	return 0;
}