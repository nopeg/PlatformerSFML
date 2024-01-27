#include "Common.h"
#include "Camera.h"
#include "Player.h"

//конструктор
Player::Player() {}
Player::Player(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime)
{
	set(ugrid, size, position, texture, imageCount, switchTime);
}

//создаем и настраиваем игрока
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

//принимаем урон
void Player::takeDamage(float damage)
{
	clock.restart();
	hurt = true;
	this->health -= damage;
	this->body->setFillColor(Color::Red);
}

//обновление
void Player::update(const float& dt, UniGrid& ugrid, Camera* cam)
{
	//передвижение камеры за игроком
	cam->move(cam->shape.getPosition(), this->body->getPosition());

	if (hurt)
	{
		//добавляем эффект получения урона и тряску камеры на некоторое время
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
			//на полу
			speed = nSpeed;
			airTime = 0;
			ground = true;
		}
		else if (body->onObject == objectType::spikes)
		{
			//мнгновенная смерть
			takeDamage(100);
		}
	}
	else
	{
		ground = false;
		speed = aSpeed;
	}

	//управление игроком
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space))
	{
		//система прыжка
		if (canJump)
		{
			if (jump < body->weight * jumpForce)
			{
				//плавный прыжок
				jump = lerp(jump, body->weight * jumpForce, dt * jaccel);
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
				//если время койота не истекло, можно отпрыгнуть от воздуха
				airTime = lerp(airTime, coyotte, dt);
			}
			else
			{
				canJump = false;
			}
		}
		jump = 0;
	}

	//горизонтальное передвижение
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

	//обновление анимаций
	if (ground)
	{
		if ((left && right) || (!left && !right))
		{
			velGoal = 0;
			animation.update(anim::idle, animReverse, dt);
		}
		else
		{
			animation.update(anim::walk, animReverse, dt);
		}
	}
	else
	{
		if ((left && right) || (!left && !right))
		{
			velGoal = 0;
		}
		animation.update(anim::jump, animReverse, dt);
	}
	body->setTextureRect(animation.uvRect);


	//передвижение
	body->velocity.x = lerp(body->velocity.x, velGoal, dt * haccel);
	body->velocity.y = lerp(body->velocity.y, body->weight - jump, dt * vaccel);

	body->checkCollision(ugrid, dt);

	body->move(body->velocity * dt);
}