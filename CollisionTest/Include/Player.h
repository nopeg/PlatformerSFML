#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
	float frict = 0.0;
	Vector2f input2f;

	void move(const float& dt, Vector2f dir);
	void checkInput();

public:
	float speed = 260;
	float friction = 1.1; //should be higher than 1
	RectangleShape shape;

	Player();
	Player(Vector2f size, Vector2f position);

	void set(Vector2f size, Vector2f position);
	void update(const float& dt);
};

#endif