#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Animation.h"

class Enemy
{
private:
	float speed = 0.1f;
	float accel = 1000.0f;
	UniGrid* unigrid;
	Animation animation;
	std::vector<Vector2f> goals;

	void moveToPoint(const float& dt, const Vector2f& point);

public:
	Entity* body;

	Enemy();
	Enemy(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);

	void set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);
	void update(const float& dt, UniGrid& ugrid, Entity* player);
};

#endif