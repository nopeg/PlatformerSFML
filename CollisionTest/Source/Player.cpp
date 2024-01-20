#include "Common.h"
#include "Camera.h"
#include "Player.h"

Player::Player() {}
Player::Player(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	set(ugrid, size, position, texture, imageCount, switchTime);
}

void Player::set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	body = new Entity(ugrid, position, size, objectType::player);
	body->checkCell(ugrid);
	body->setOutlineThickness(0);
	body->mass = 100;
	body->weight = body->mass * gravity;

	animation.set(texture, imageCount, switchTime);
	animation.update(0, 0, 0);
	body->setTexture(texture);
	body->setTextureRect(animation.uvRect);
}

void Player::takeDamage(float damage)
{
	clock.restart();
	hurt = true;
	this->health -= damage;
	this->body->setFillColor(Color::Red);
}

void Player::update(const float& dt, UniGrid& ugrid, Camera* cam)
{
	if (hurt)
	{
		seconds = clock.getElapsedTime().asSeconds();

		if (seconds < 0.1f)
		{
			cam->randShake(randRangeF(2, 3));
		}
		else
		{
			cam->resetRotation();
			this->body->setFillColor(Color::White);
			hurt = false;
		}
	}

	if (body->onGround)
	{
		if (body->onObject == objectType::wall || body->onObject == objectType::enemy)
		{
			speed = nSpeed;
			airTime = 0;
			ground = true;
		}
		else if (body->onObject == objectType::spikes)
		{
			takeDamage(100);
		}
	}
	else
	{
		speed = aSpeed;
	}

	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (canJump)
		{
			if (jump < body->weight * jumpForce)
			{
				jump = smooth(jump, body->weight * jumpForce, dt * jaccel);
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
		if (ground)
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
		animReverse = 1;
	}
	else
	{
		left = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		velGoal = speed;
		right = true;
		animReverse = 0;
	}
	else
	{
		right = false;
	}

	if ((left && right) || (!left && !right))
	{
		velGoal = 0;
		if (ground)
		{
			animation.update(0, animReverse, dt);
		}
		else
		{
			animation.update(2, animReverse, dt);
		}
	}
	else if (ground)
	{
		animation.update(1, animReverse, dt);
	}
	else
	{
		animation.update(2, animReverse, dt);
	}

	body->setTextureRect(animation.uvRect);

	body->velocity.x = smooth(body->velocity.x, velGoal, dt * haccel);
	body->velocity.y = smooth(body->velocity.y, body->weight - jump, dt * vaccel);

	body->checkCollision(ugrid, dt);

	body->move(body->velocity * dt);
}