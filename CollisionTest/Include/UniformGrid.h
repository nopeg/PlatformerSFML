#ifndef UGRID_H
#define UGRID_H

#include <SFML/Graphics.hpp>

class Entity;

//класс физической сетки, котора€ делит мир на €чейки дл€ устранени€ ненужных вычислений
class UniGrid
{
private:
	//массив сетки из физических объектов
	std::vector<std::vector<std::vector<Entity*>>> grid;

public:
	//параметры сетки
	float cellSize = 32.0f * 16;
	unsigned int height = 10;
	unsigned int width = 10;

	//функции
	void createGrid();
	Vector2i getCell(const Vector2f& coords);
	std::vector<Vector2i> getCells(const std::vector<Vector2f>& points);
	std::vector<Entity*> getBodies(const Vector2f& coords);
	int contains(const Vector2i& coords, Entity* body);

	void add(const Vector2f& coords, Entity* body);
	void remove(const Vector2i& coords, Entity* body);
};

#endif