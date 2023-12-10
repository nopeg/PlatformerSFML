#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "UniformGrid.h"

class Entity : public RectangleShape
{
private:
	std::vector<Vector2i> cells;
	std::vector<Vector2i> prevCells;
	std::vector<Entity*> nearBodies;

public:
	int id = 0;
	float mass = 0;
	float weight = 0;
	float friction = 1.1f; //should be higher than 1
	bool onGround = false;
	Vector2f velocity;

	Entity();
	Entity(UniGrid& ugrid, Vector2f p);
	void create(UniGrid& ugrid, Vector2f p);
	std::vector<Vector2f> getPoints();
	void checkCell(UniGrid& ugrid);

	bool checkCollision(UniGrid& ugrid, const float& dt);
	bool rayToRectangle(const Vector2f& rayOrigin, const Vector2f& rayDirection,
		const RectangleShape* target, Vector2f& normal, float& timeHit);
	bool rectangleCollision(const Entity* r1, const Entity& r2, Vector2f& normal, const float dt, float& ct);
	bool resolveCollision(Entity* r1, Entity* r2, const float dt);

};

#endif
