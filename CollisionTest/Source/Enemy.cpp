#include "Common.h"
#include "Enemy.h"
#include "Player.h"

//������������
Enemy::Enemy() {}
Enemy::Enemy(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	set(ugrid, size, position, texture, imageCount, switchTime);
}

//������� � ����������� �����
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

//���������� �����
void Enemy::update(const float& dt, UniGrid& ugrid, Player* player)
{
	//��������
	animation.update(0, 0, dt);
	body->setTextureRect(animation.uvRect);

	//���� ���������� � ������, �������� �� �����
	if (body->onObject == objectType::spikes && canFly)
	{
		clock.restart();
		body->velocity *= 0.0f;
		canFly = false;
	}

	//���� ���������� �� ������ ��������� � ��������� �����������
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
			//���� ����� ������, ��������� � ��������� �������������
			currentState = state::chase;
		}
		else if (distance(body->getPosition(), player->body->getPosition()) <= 64.0f)
		{
			//���� ����� � ������� ������� ���
			currentState = state::attack;
		}
		else
		{
			//����� ������ �� ������
			currentState = state::sleep;
		}
	}

	//��������� ���������
	switch (currentState)
	{
	case state::sleep:
		body->velocity = lerp2f(body->velocity, Vector2f(0, 0), dt * accel);
		break;

	case state::chase:
		body->velocity = lerp2f(body->velocity, player->body->getPosition() - body->getPosition(), dt * accel);
		break;

	case state::attack:
		//������� ������ 1.5 �������
		sec = clock.getElapsedTime().asSeconds();
		if (sec > 1.5f)
		{
			player->takeDamage(randRange(5, 15));
			clock.restart();
		}
		break;

	case state::retreat:
		//������������ �� ��� ������� � ��������� �����, ����������� ������������ �� ������
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

	//���� �� ����� ���� ����� ���������
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