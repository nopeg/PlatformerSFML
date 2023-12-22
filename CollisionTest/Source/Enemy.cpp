#include "Common.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() {}
Enemy::Enemy(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	set(ugrid, size, position, texture, imageCount, switchTime);
}

void Enemy::set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	body = new Entity(ugrid, position, size);
	body->checkCell(ugrid);
	body->setOutlineThickness(0);
	body->mass = 4500;
	body->id = 99999;
	body->weight = body->mass * gravity;

	animation.set(texture, imageCount, switchTime);
	animation.update(0, 0, 0);
	body->setTexture(texture);
	body->setTextureRect(animation.uvRect);
}

void Enemy::update(const float& dt, UniGrid& ugrid, Player* player)
{
	animation.update(0, 0, dt);
	body->setTextureRect(animation.uvRect);

	if (distance(body->getPosition(), player->body->getPosition()) < 1000.0f 
		&& distance(body->getPosition(), player->body->getPosition()) > 64.0f)
	{
		body->velocity.x = smooth(body->velocity.x, -(body->getPosition() - player->body->getPosition()).x, dt * accel);
		body->velocity.y = smooth(body->velocity.y, -(body->getPosition() - player->body->getPosition()).y, dt * accel);
	}
	else if (distance(body->getPosition(), player->body->getPosition()) <= 64.0f)
	{
		msec = static_cast<unsigned int>(clock.getElapsedTime().asMilliseconds());

		if (msec >= 1000)
		{
			player->health -= 10.0f;
			clock.restart();
		}
	}
	else
	{
		body->velocity.x = smooth(body->velocity.x, 0, dt * accel);
		body->velocity.y = smooth(body->velocity.y, 0, dt * accel);
	}

	body->checkCollision(ugrid, dt);
	body->move(body->velocity * dt );
}