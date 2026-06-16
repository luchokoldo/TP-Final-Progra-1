#include <stdio.h>
#include <stdlib.h>

#include "gym.h"
#include "menu.h"

int main()
{
	Gym gym = { 0 };

	GymCargarDatos(&gym);

	MenuMostrarMenu(&gym);

	return 0;
}