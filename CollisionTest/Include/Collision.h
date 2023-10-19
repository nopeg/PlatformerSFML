#pragma once
class Collider
{
	std::vector<UniformCell*> currentCells;
	void getLocalObjects()
	{
		for (int i = 0; i < currentCells.size(); i++)
		{
			for (int j = 0; j < currentCells[i]->objects.size(); j++)
			{

			}
		}
	}
};
class UniformCell
{
public:
	std::vector<Collider*> objects;
	void add(Collider* object);
	void del(Collider* object);
};
class UniformGrid
{
	float cellSize = 128.0f;
	unsigned int height = 8;
	unsigned int width = 8;
	std::vector<std::vector<UniformCell*>> uniGrid;
	UniformCell* getCell(Vector2f position)
	{
		return uniGrid[int(position.x / cellSize)][int(position.y / cellSize)];
	}
};