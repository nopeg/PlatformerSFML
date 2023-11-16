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

#endif