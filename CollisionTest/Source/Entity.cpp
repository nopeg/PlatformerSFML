#include "Common.h"
#include "Entity.h"

//������������� �������
Entity::Entity() {}
Entity::Entity(UniGrid& ugrid, Vector2f p, Vector2f s, objectType type)
{
	create(ugrid, p, s, type);
}

void Entity::create(UniGrid& ugrid, Vector2f p, Vector2f s, objectType type)
{
	id = type;
	std::cout << "add " << id << std::endl;

	this->setSize(s);
	this->setOrigin(getSize().x / 2, getSize().y / 2);
	this->setPosition(p);
	this->setFillColor(Color::White);
	this->setOutlineThickness(2);
	this->setOutlineColor(Color::White);

	//��������� ������ � ����� �� 4 ������ ��� ��������������
	std::vector<Vector2f> points = this->getPoints();
	for (int i = 0; i < points.size(); i++)
	{
		for (float i = ugrid.getCell(points[0]).x; i < ugrid.getCell(points[3]).x + 1; i++)
		{
			for (float j = ugrid.getCell(points[0]).y; j < ugrid.getCell(points[1]).y + 1; j++)
			{
				ugrid.add({ i * ugrid.cellSize, j * ugrid.cellSize }, this);
			}
		}
	}
}

//������� 4 ����� (������� ��������������)
std::vector<Vector2f> Entity::getPoints()
{
	Vector2f point1 = { this->getGlobalBounds().left, this->getGlobalBounds().top };
	Vector2f point2 = { this->getGlobalBounds().left, this->getGlobalBounds().top + this->getGlobalBounds().height };
	Vector2f point3 = { this->getGlobalBounds().left + this->getGlobalBounds().width, 
		this->getGlobalBounds().top + this->getGlobalBounds().height };
	Vector2f point4 = { this->getGlobalBounds().left + this->getGlobalBounds().width, this->getGlobalBounds().top };
	return { point1, point2, point3, point4 };
}

//��������� ������� ������� � ����� � ������� ������ ������� � ��� �� �������
void Entity::checkCell(UniGrid& ugrid)
{
	std::vector<Vector2f> points = this->getPoints();
	prevCells = cells;
	cells = ugrid.getCells(points);

	//���� ������� ���������� ��������� ������
	if (cells != prevCells)
	{
		for (int i = 0; i < prevCells.size(); i++)
		{
			ugrid.remove(prevCells[i], this);
		}
		for (int i = 0; i < points.size(); i++)
		{
			for (float i = ugrid.getCell(points[0]).x; i < ugrid.getCell(points[3]).x + 1; i++)
			{
				for (float j = ugrid.getCell(points[0]).y; j < ugrid.getCell(points[1]).y + 1; j++)
				{
					ugrid.add({ i * ugrid.cellSize, j * ugrid.cellSize }, this);
				}
			}
		}
	}

	//�������� ���������� � ������ �������� � ��� �� �������
	nearBodies.clear();
	for (int i = 0; i < 3; i++)
	{
		std::vector<Entity*> bodies = ugrid.getBodies(points[i]);
		for (int j = 0; j < bodies.size(); j++)
		{
			if (bodies[j] != this)
			{
				nearBodies.push_back(bodies[j]);
			}
		}
	}
}

//�������� � ���������� ������������
bool Entity::checkCollision(UniGrid& ugrid, const float& dt)
{
	checkCell(ugrid);
	Vector2f n;
	float t;
	onObject = -1;
	onGround = false;

	//��������� �� ������������ � ���������� ���������
	for (int i = 0; i < nearBodies.size(); i++)
	{
		if (rectangleCollision(this, *nearBodies[i], n, dt, t))
		{
			//������������ � ��������� ������������
			resolveCollision(this, nearBodies[i], dt);
			//� ����� ����� ������� ����������
			onObject = nearBodies[i]->id;
			//���� ���������� �� ��������� � �������� �� �������
			if (n.y == -1)
			{
				onGround = true;
			}
		}
	}

	return 0;
}

//�������� ��� �� �������� ����� � ����������� �������, ����� ��������� ������������
bool Entity::rayToRectangle(const Vector2f& rayOrigin, const Vector2f& rayDirection,
	const RectangleShape* target, Vector2f& normal, float& timeHit)
{
	normal = { 0,0 };
	Vector2f point = { 0,0 };

	Vector2f invdir = { 1 / rayDirection.x,  1 / rayDirection.y };

	//����� �����
	Vector2f enter =
	{
		(target->getGlobalBounds().left - rayOrigin.x) * invdir.x,
		(target->getGlobalBounds().top - rayOrigin.y) * invdir.y
	};
	//����� ������
	Vector2f exit =
	{
		(target->getGlobalBounds().left + target->getGlobalBounds().width - rayOrigin.x) * invdir.x,
		(target->getGlobalBounds().top + target->getGlobalBounds().height - rayOrigin.y) * invdir.y
	};

	//���� ��� � ������ �� �����������
	if (std::isnan(exit.y) || std::isnan(exit.x))
		return false;
	if (std::isnan(enter.y) || std::isnan(enter.x))
		return false;

	//�������� �� ���������������� ������������
	if (enter.x > exit.x)
		std::swap(enter.x, exit.x);
	if (enter.y > exit.y)
		std::swap(enter.y, exit.y);

	if (enter.x > exit.y || enter.y > exit.x)
		return false;

	//����������� "����� (�����������������)" ������������
	timeHit = std::max(enter.x, enter.y);
	float timeSecondHit = std::min(exit.x, exit.y);

	if (timeSecondHit < 0)
		return false;

	//����� ������������
	point = rayOrigin + timeHit * rayDirection;

	//������ �������
	if (enter.x > enter.y)
	{
		if (invdir.x < 0)
		{
			normal = { 1, 0 };
		}
		else
		{
			normal = { -1, 0 };
		}
	}
	else if (enter.x < enter.y)
	{
		if (invdir.y < 0)
		{
			normal = { 0, 1 };
		}
		else
		{
			normal = { 0, -1 };
		}
	}

	return true;
}

//�������� ������������ ����� ����� �������������� ��������
bool Entity::rectangleCollision(const Entity* r1, const Entity& r2, Vector2f& normal, const float dt, float& ct)
{
	//���� ������� ����������, �� ���������
	if (r1->velocity.x == 0 && r1->velocity.y == 0)
		return false;

	//����������� ������� ������� �������
	RectangleShape target;
	target.setPosition(Vector2f(r2.getGlobalBounds().left, r2.getGlobalBounds().top) - 
		Vector2f(r1->getGlobalBounds().width, r1->getGlobalBounds().height) / 2.0f);

	target.setSize(Vector2f(r2.getGlobalBounds().width, r2.getGlobalBounds().height) + 
		Vector2f(r1->getGlobalBounds().width, r1->getGlobalBounds().height));

	//�������� �������� ������������ ����� �����, ����������� �� ������� �������, � ������ ��������
	if (rayToRectangle(Vector2f(r1->getGlobalBounds().left, r1->getGlobalBounds().top) + 
		Vector2f(r1->getGlobalBounds().width, r1->getGlobalBounds().height) / 2.0f,
		r1->velocity * dt, &target, normal, ct))
	{
		return (ct >= 0.0f && ct < 1.0f);
	}
	else
	{
		return false;
	}
}

//��������� ������������ ����� ����� ���������, ������� �� �������� � �������������� �����������
bool Entity::resolveCollision(Entity* r1, Entity* r2, const float dt)
{
	Vector2f normal;
	float ct = 0.0f;
	if (rectangleCollision(r1, *r2, normal, dt, ct))
	{
		r1->velocity += Vector2f(std::abs(r1->velocity.x) * normal.x,
			std::abs(r1->velocity.y) * normal.y) * (1 - ct);
		return true;
	}

	return false;
}
