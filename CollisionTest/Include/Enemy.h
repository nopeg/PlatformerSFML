#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Animation.h"

class Player;
//перечисления состояний врагов
enum state { sleep, chase, attack, retreat, death };

//класс врагов
class Enemy
{
private:
	//переменные
	state currentState = state::sleep;
	float speed = 0.1f;
	bool canFly = true;
	float accel = 1000.0f;
	UniGrid* unigrid;
	Animation animation;
	std::vector<Vector2f> goals;
	Clock clock;
	int sec;

public:
	//берем объект класса entity, чтобы не наследовать его
	Entity* body;

	//конструктор
	Enemy();
	Enemy(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);

	//функции
	void set(UniGrid& ugrid, Vector2f size, Vector2f position, Texture* texture, Vector2u imageCount, float switchTime);
	void update(const float& dt, UniGrid& ugrid, Player* player);
};

#endif