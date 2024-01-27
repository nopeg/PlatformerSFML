#ifndef COMMON_H
#define COMMON_H
//������� �������, ������������ �� ���� �������

//����������� ����������
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <fstream>
#include <sstream>

//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//���������
#define gravity 9.8
#define PI 3.1415926

//���� ����� ����� ��������� � ��������
inline float angle(Vector2f point1, Vector2f point2)
{
	return atan2(point1.y - point2.y, point1.x - point2.x);
}

//���������� ����� ����� ���������
inline float distance(Vector2f point1, Vector2f point2)
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

//����������� ������ �������� � ������������� � �������� �������� (��� ���������)
inline float convertMinMax(float min1, float max1, float min2, float max2, float pos)
{
	return min1 + ((pos - max2) / min2 * (max1 - min1));
}

//�������� ������������
inline float lerp(float a, float b, float f)
{
	float diff = b - a;

	if (diff > f)
		return a + f;

	if (diff < -f)
		return a - f;

	return b;
}
inline Vector2f lerp2f(const Vector2f& pointA, const Vector2f& pointB, float f) 
{
	if (f > 1.f)
		f = 1.f;

	else if (f < 0.f)
		f = 0.f;

	return pointA + (pointB - pointA) * f;
}

//����������� � ��������
template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

//���������� ���������
inline std::vector<float> sortBubble(std::vector<float> vector, int length)
{
	int temp = 0;
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (vector[i] > vector[j])
			{
				temp = vector[i];
				vector[i] = vector[j];
				vector[j] = temp;
			}
		}
	}
	return vector;
}

//�������� ���� �������� �� ������ ����� ���� � ������
inline std::string removeChars(std::string& s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (!std::isdigit(s[i]) && !std::isspace(s[i]) && s[i] != '-')
		{
			s.erase(i);
		}
	}
	return s;
}


//��������� ��������� �����
inline int randRange(int min, int max)
{
	std::random_device randDevice;
	std::mt19937_64 generator(randDevice());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(randDevice);
}
inline float randRangeF(float min, float max)
{
	std::random_device randDevice;
	std::mt19937_64 generator(randDevice());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(randDevice);
}

//����� ���������� �������� �� �������
template <class T>
inline T randPick(std::vector<T> vector)
{
	if (vector.size() > 0)
	{
		int r = randRange(0, vector.size() - 1);
		return vector[r];
	}
}

#endif