#ifndef UGRID_H
#define UGRID_H

#include <SFML/Graphics.hpp>

class Entity;

class UniGrid
{
private:
	std::vector<std::vector<std::vector<Entity*>>> grid;

public:
	float cellSize = 32.0f * 16;
	unsigned int height = 10;
	unsigned int width = 10;

	void createGrid();
	Vector2i getCell(const Vector2f& coords);
	std::vector<Vector2i> getCells(const std::vector<Vector2f>& points);
	std::vector<Entity*> getBodies(const Vector2f& coords);
	int contains(const Vector2i& coords, Entity* body);

	void add(const Vector2f& coords, Entity* body);
	void remove(const Vector2i& coords, Entity* body);
};

#endif