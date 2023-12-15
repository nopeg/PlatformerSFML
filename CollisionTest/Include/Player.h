#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player
{
private:
	float speed = 0.0f;
	float jump = 0.0f;
	bool left = false;
	bool right = false;
	bool canJump = false;
	float airTime = 0.0f;
	UniGrid* unigrid;


public:
	Entity* body;
	float nSpeed = 800;
	float aSpeed = nSpeed / 2;
	float jumpHeight = 180;
	float coyotte = 0.3;
	float accel = 1000.0f;
	float jaccel = 1500.0f;

	Player();
	Player(UniGrid& ugrid, Vector2f size, Vector2f position);

	void set(UniGrid& ugrid, Vector2f size, Vector2f position);
	void update(const float& dt, UniGrid& ugrid);
};

#endif