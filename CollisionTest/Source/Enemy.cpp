#include "Common.h"
#include "Enemy.h"
#include "Player.h"

//конструкторы
Enemy::Enemy() {}
Enemy::Enemy(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	set(ugrid, size, position, texture, imageCount, switchTime);
}

//создаем и настраиваем врага
void Enemy::set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	body = new Entity(ugrid, position, size, objectType::enemy);
	body->checkCell(ugrid);
	body->setOutlineThickness(0);
	body->mass = 4500;
	body->weight = body->mass * gravity;

	animation.set(texture, imageCount, switchTime);
	animation.update(0, 0, 0);
	body->setTexture(texture);
	body->setTextureRect(animation.uvRect);
}

//обновление врага
void Enemy::update(const float& dt, UniGrid& ugrid, Player* player)
{
	//анимация
	animation.update(0, 0, dt);
	body->setTextureRect(animation.uvRect);

	//если столкнулся с шипами, остается на месте
	if (body->onObject == objectType::spikes && canFly)
	{
		clock.restart();
		body->velocity *= 0.0f;
		canFly = false;
	}

	//если столкнулся со стеной переходит в состояние отступления
	if (body->onObject == objectType::wall)
	{
		currentState = state::retreat;
		clock.restart();
	}
	else if (currentState != state::retreat)
	{
		if (distance(body->getPosition(), player->body->getPosition()) < 1000.0f
			&& distance(body->getPosition(), player->body->getPosition()) > 64.0f)
		{
			//если видит игрока, переходит в состояние преследования
			currentState = state::chase;
		}
		else if (distance(body->getPosition(), player->body->getPosition()) <= 64.0f)
		{
			//если рядом с игроком атакует его
			currentState = state::attack;
		}
		else
		{
			//иначе ничего не делает
			currentState = state::sleep;
		}
	}

	//обработка состояний
	switch (currentState)
	{
	case state::sleep:
		body->velocity = lerp2f(body->velocity, Vector2f(0, 0), dt * accel);
		break;

	case state::chase:
		body->velocity = lerp2f(body->velocity, player->body->getPosition() - body->getPosition(), dt * accel);
		break;

	case state::attack:
		//атакует каждые 1.5 секунды
		sec = clock.getElapsedTime().asSeconds();
		if (sec > 1.5f)
		{
			player->takeDamage(randRange(5, 15));
			clock.restart();
		}
		break;

	case state::retreat:
		//перемещается на пол секунды в случайную точку, симметрично направленную от игрока
		sec = clock.getElapsedTime().asSeconds();
		if (sec < 0.5f)
		{
			body->velocity.x = lerp(body->velocity.x, randPick<int>({ -160, 160 }) + 
				(body->getPosition() - player->body->getPosition()).x, dt * accel);
			body->velocity.y = lerp(body->velocity.y, randPick<int>({ -160, 160 }) +
				(body->getPosition() - player->body->getPosition()).y, dt * accel);
		}
		else
		{
			currentState = state::sleep;
		}
		break;
	}

	//если не задел шипы может двигаться
	if (canFly)
	{
		body->checkCollision(ugrid, dt);
		body->move(body->velocity * dt);
	}
	else
	{
		body->rotate(2);
	}
}