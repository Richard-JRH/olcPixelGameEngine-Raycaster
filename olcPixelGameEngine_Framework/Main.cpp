#define OLC_PGE_APPLICATION
#include "Raycaster.h"

void main()
{
	Raycaster App;

	if (App.Construct(800, 600, 1, 1))
		App.Start();
}