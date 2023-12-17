#include "Common.h"
#include "Player.h"

Player::Player() {}
Player::Player(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	set(ugrid, size, position, texture, imageCount, switchTime);
}

void Player::set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	body = new Entity(ugrid, position);
	body->checkCell(ugrid);
	body->setOutlineThickness(0);
	body->mass = 100;
	body->id = 100000;
	body->setOrigin(Vector2f(size.x / 2, size.y / 2));
	body->setSize(size);
	body->setPosition(position);
	body->weight = body->mass * gravity;

	animation.set(texture, imageCount, switchTime);
	body->setTexture(texture);
}

void Player::update(const float& dt, UniGrid& ugrid)
{
	if (body->onGround)
	{
		speed = nSpeed;
		airTime = 0;
	}
	else
	{
		speed = aSpeed;
	}

	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (canJump)
		{
			if (jump < body->weight * 29)
			{
				jump = smooth(jump, body->weight * 29, dt * 200000);
			}
			else
			{
				canJump = false;
				jump = 0;
			}
		}
	}
	else
	{
		if (body->onGround)
		{
			canJump = true;
		}
		else
		{
			if (airTime < coyotte && jump == 0)
			{
				airTime = smooth(airTime, coyotte, dt);
			}
			else
			{
				canJump = false;
			}
		}
		jump = 0;
	}

	float velGoal;
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		velGoal = -speed;
		left = true;
	}
	else
	{
		left = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		velGoal = speed;
		right = true;
	}
	else
	{
		right = false;
	}

	if ((left && right) || (!left && !right))
	{
		velGoal = 0;
	}

	animation.update(0, 0, dt);
	body->setTextureRect(animation.uvRect);

	body->velocity.x = smooth(body->velocity.x, velGoal, dt * accel);
	body->velocity.y = smooth(body->velocity.y, body->weight - jump, dt * jaccel);

	body->checkCollision(ugrid, dt);

	body->move(body->velocity * dt);
}