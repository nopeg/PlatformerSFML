#include "Common.h"
#include <iostream>
#include "WorldGrid.h"

void WorldGrid::createGrid()
{
	grid.resize(height);
	for (int i = 0; i < height; i++)
	{
		grid[i].resize(width);
	}
}