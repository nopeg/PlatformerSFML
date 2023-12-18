#ifndef WGRID_H
#define WGRID_H

#include <SFML/Graphics.hpp>

class WorldGrid
{
private:
	std::vector<std::vector <int>> grid;

public:
	float cellSize = 32.0f * 16;
	unsigned int height = 10;
	unsigned int width = 10;

	void createGrid();

};

#endif