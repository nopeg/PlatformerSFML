#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "UniformGrid.h"

//перечисление типов объектов
enum objectType { wall, spikes, player, enemy };

//класс физического объекта, наследующий класс пр€моуголной фигуры
class Entity : public RectangleShape
{
private:
	//координаты €чеек
	std::vector<Vector2i> cells;
	std::vector<Vector2i> prevCells;

public:
	//переменные класса
	objectType id = objectType::wall;
	float mass = 0;
	float weight = 0;
	int onObject = -1;
	bool onGround = false;
	std::vector<Entity*> nearBodies;
	Vector2f velocity;

	//инициализаци€
	Entity();
	Entity(UniGrid& ugrid, Vector2f p, Vector2f s, objectType type);
	void create(UniGrid& ugrid, Vector2f p, Vector2f s, objectType type);
	//функции дл€ работы с сеткой
	std::vector<Vector2f> getPoints();
	void checkCell(UniGrid& ugrid);
	//функции физики
	bool checkCollision(UniGrid& ugrid, const float& dt);
	bool rayToRectangle(const Vector2f& rayOrigin, const Vector2f& rayDirection,
		const RectangleShape* target, Vector2f& normal, float& timeHit);
	bool rectangleCollision(const Entity* r1, const Entity& r2, Vector2f& normal, const float dt, float& ct);
	bool resolveCollision(Entity* r1, Entity* r2, const float dt);

};

#endif
