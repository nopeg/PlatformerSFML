#include "Common.h"
#include "UniformGrid.h"

//������� �������
void UniGrid::createGrid()
{
	grid.resize(height);
	for (int i = 0; i < height; i++)
	{
		grid[i].resize(width);
	}
}

//�������� ��������� ���������� ������ � ����� �� ���������� ��������� � ����
Vector2i UniGrid::getCell(const Vector2f& coords)
{
	int y = clamp<int>(int(coords.y / cellSize), 0, height - 1);
	int x = clamp<int>(int(coords.x / cellSize), 0, width - 1);
	return { x, y };
}

//��������� ���������� ���������� �����
std::vector<Vector2i> UniGrid::getCells(const std::vector<Vector2f>& points)
{
	std::vector<Vector2i> vector;
	vector.push_back(getCell(points[0]));
	for (int i = 1; i < points.size(); i++)
	{
		for (int j = 0; j < vector.size(); j++)
		{
			if (vector[j] != getCell(points[i]))
			{
				vector.push_back(getCell(points[i]));
			}
		}
	}
	return vector;
}

//�������� ���������� ������� ������ �� ���������� �����������
std::vector<Entity*> UniGrid::getBodies(const Vector2f& coords)
{
	std::vector<Entity*> vector;
	for (int i = 0; i < grid[getCell(coords).y][getCell(coords).x].size(); i++)
	{
		vector.push_back(grid[getCell(coords).y][getCell(coords).x][i]);
	}
	return vector;
}

//�������� ������ �� ���������� ������������ �������
int UniGrid::contains(const Vector2i& coords, Entity* body)
{
	int result = -1;
	for (unsigned int i = 0; i < grid[coords.y][coords.x].size(); i++)
	{
		if (grid[coords.y][coords.x][i] == body)
		{
			result = i;
		}
	}

	return result;
}

//��������� ������ � ������ �� ���������� �����������
void UniGrid::add(const Vector2f& coords, Entity* body)
{
	if (contains(getCell(coords), body) == -1)
		grid[getCell(coords).y][getCell(coords).x].push_back(body);
}

//������� ������ �� ������ � ��������� �����������
void UniGrid::remove(const Vector2i& coords, Entity* body)
{
	int b = contains(coords, body);
	if (b != -1)
		grid[coords.y][coords.x].erase(grid[coords.y][coords.x].begin() + b);
}