#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "UniformGrid.h"

//������������ ����� ��������
enum objectType { wall, spikes, player, enemy };

//����� ����������� �������, ����������� ����� ������������ ������
class Entity : public RectangleShape
{
private:
	//���������� �����
	std::vector<Vector2i> cells;
	std::vector<Vector2i> prevCells;

public:
	//���������� ������
	objectType id = objectType::wall;
	float mass = 0;
	float weight = 0;
	int onObject = -1;
	bool onGround = false;
	std::vector<Entity*> nearBodies;
	Vector2f velocity;

	//�������������
	Entity();
	Entity(UniGrid& ugrid, Vector2f p, Vector2f s, objectType type);
	void create(UniGrid& ugrid, Vector2f p, Vector2f s, objectType type);
	//������� ��� ������ � ������
	std::vector<Vector2f> getPoints();
	void checkCell(UniGrid& ugrid);
	//������� ������
	bool checkCollision(UniGrid& ugrid, const float& dt);
	bool rayToRectangle(const Vector2f& rayOrigin, const Vector2f& rayDirection,
		const RectangleShape* target, Vector2f& normal, float& timeHit);
	bool rectangleCollision(const Entity* r1, const Entity& r2, Vector2f& normal, const float dt, float& ct);
	bool resolveCollision(Entity* r1, Entity* r2, const float dt);

};

#endif
