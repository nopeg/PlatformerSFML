#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Animation.h"

class Camera;

class Player
{
private:
	float speed = 0.0f;
	float jump = 0.0f;
	bool hurt = false;
	bool animReverse;
	bool left = false;
	bool right = false;
	bool canJump = false;
	float airTime = 0.0f;
	UniGrid* unigrid;
	Animation animation;

	Clock clock;
	float seconds;

public:
	Entity* body;
	float health = 100.0f;
	float nSpeed = 800;
	float aSpeed = nSpeed / 3;
	float jumpForce = 30;
	float coyotte = 0.05;
	float haccel = 1000.0f;
	float vaccel = 10000.0f;
	float jaccel = 200000.0f;

	Player();
	Player(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);

	void takeDamage(float damage);
	void set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);
	void update(const float& dt, UniGrid& ugrid, Camera* cam);
};

#endif