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
	body = new Entity(ugrid, position);
	body->checkCell(ugrid);
	body->setOutlineThickness(0);
	body->mass = 4500;
	body->id = 99999;
	body->setOrigin(Vector2f(size.x / 2, size.y / 2));
	body->setSize(size);
	body->setPosition(position);
	body->weight = body->mass * gravity;

	animation.set(texture, imageCount, switchTime);
	body->setTexture(texture);
}

void Enemy::moveToPoint(const float& dt, const Vector2f& point)
{

	body->move(body->velocity * dt);
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
	//body->setRotation(angle(body->getPosition(), player->getPosition()));

	body->checkCollision(ugrid, dt);
	body->move(body->velocity * dt );
}