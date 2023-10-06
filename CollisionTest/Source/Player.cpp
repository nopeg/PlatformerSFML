#include "Common.h"
#include "Player.h"

Player::Player() {}
Player::Player(Vector2f size, Vector2f position)
{
	set(size, position);
}

void Player::set(Vector2f size, Vector2f position)
{
	shape.setOrigin(Vector2f(size.x / 2, size.y / 2));
	shape.setSize(size);
	shape.setPosition(position);
}

void Player::move(const float& dt, Vector2f dir)
{
	shape.move(dir * dt * speed * frict);
}

void Player::checkInput()
{
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		input2f.x = -1.0;
		frict = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		input2f.x = 1.0;
		frict = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		input2f.y = -1.0;
		frict = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		input2f.y = 1.0;
		frict = 1;
	}
}

void Player::update(const float& dt)
{
	if (frict <= 0.005)
	{
		input2f.x = 0.0;
		input2f.y = 0.0;
		frict = 0;
	}

	checkInput();

	if (sqrt(input2f.x * input2f.x + input2f.y * input2f.y) > 1.0)
	{
		input2f.x /= std::sqrt(2.0);
		input2f.y /= std::sqrt(2.0);
	}

	frict /= friction;

	move(dt, input2f);
}