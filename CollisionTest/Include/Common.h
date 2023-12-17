#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

#define gravity 9.8
#define PI 3.1415926
#define print(x) std::cout << x << std::endl;

//returns angle between two objects in radians
inline float angle(Vector2f point1, Vector2f point2)
{
	return atan2(point1.y - point2.y, point1.x - point2.x);
}

//returns distance between two objects
inline float distance(Vector2f point1, Vector2f point2)
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

//returns converted values with min and max limits between each other (for sliders)
inline float convertMinMax(float min1, float max1, float min2, float max2, float pos)
{
	return min1 + ((pos - max2) / min2 * (max1 - min1));
}

//linear interpolation
inline float lerp(float a, float b, float fraction)
{
	return (a * (1.0 - fraction)) + (b * fraction);
}

inline float smooth(float a, float b, float dt)
{
	float diff = b - a;

	if (diff > dt)
		return a + dt;

	if (diff < -dt)
		return a - dt;

	return b;
}

inline Vector2f interpolate(const Vector2f& pointA, const Vector2f& pointB,float factor) 
{
	if (factor > 1.f)
		factor = 1.f;

	else if (factor < 0.f)
		factor = 0.f;

	return pointA + (pointB - pointA) * factor;
}

//clamping between min and max
template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

//returns sorted vector
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

//returns random value
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

//returns random element of vector
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