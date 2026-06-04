#include <stdio.h>
#include <stdlib.h>

#include "gym.h"
#include "archivos.h"
#include "menu.h"

int main()
{
	Gym gym = { 0 };


	ArchivoCargarGym(&gym);

	MostrarMenu(&gym);

	ArchivoGuardarGym(&gym);

	return 0;
}