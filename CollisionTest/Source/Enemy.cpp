#include "Common.h"
#include "Enemy.h"

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

void Enemy::update(const float& dt, UniGrid& ugrid, Entity* player)
{
	animation.update(0, 0, dt);
	body->setTextureRect(animation.uvRect);

	if (distance(body->getPosition(), player->getPosition()) <= 1000.0f)
	{
		body->velocity.x = smooth(body->velocity.x, -(body->getPosition() - player->getPosition()).x, dt * accel);
		body->velocity.y = smooth(body->velocity.y, -(body->getPosition() - player->getPosition()).y, dt * accel);
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