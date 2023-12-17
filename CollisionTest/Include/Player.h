#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Animation.h"

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
	Animation animation;

public:
	Entity* body;
	float nSpeed = 800;
	float aSpeed = nSpeed / 3;
	float jumpHeight = 2500;
	float coyotte = 0.05;
	float accel = 1000.0f;
	float jaccel = 10000.0f;

	Player();
	Player(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);

	void set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);
	void update(const float& dt, UniGrid& ugrid);
};

#endif