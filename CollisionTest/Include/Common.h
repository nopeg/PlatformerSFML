#ifndef COMMON_H
#define COMMON_H

#include <math.h>

//calculates angle between two objects in radians
inline double angle(double x1, double y1, double x2, double y2)
{
	double a = atan2(y1 - y2, x1 - x2);
	return a;
}
inline float angle(float x1, float y1, float x2, float y2)
{
	float a = atan2(y1 - y2, x1 - x2);
	return a;
}

//calculates distance between two objects
inline double distance(double x1, double y1, double x2, double y2)
{
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return d;
}
inline float distance(float x1, float y1, float x2, float y2)
{
	float d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return d;
}

//converting values that have min and max limits between each other
inline double convertMinMax(double min1, double max1, double min2, double max2, double pos)
{
	return min1 + ((pos - max2) / min2 * (max1 - min1));
}
inline float convertMinMax(float min1, float max1, float min2, float max2, float pos)
{
	return min1 + ((pos - max2) / min2 * (max1 - min1));
}

//bubble array sorting
inline std::vector<int> sortArrayB(std::vector<int> a, int arrayLength)
{
	int temp;
	for (int i = 0; i < arrayLength; i++)
	{
		for (int j = i + 1; j < arrayLength; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	return a;
}
inline std::vector<double> sortArrayB(std::vector<double> a, int arrayLength)
{
	double temp;
	for (int i = 0; i < arrayLength; i++)
	{
		for (int j = i + 1; j < arrayLength; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	return a;
}


//random range int
inline int randRange(int min, int max)
{
	int r = min + (rand() * (int)(max - min) / RAND_MAX);
	return r;
}
inline float randRange(float min, float max)
{
	float r = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return r;
}
inline double randRange(double min, double max)
{
	double r = min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
	return r;
}

//random number picker
inline int randPick(std::vector<int> vector)
{
	int ranV = randRange(0, vector.size());
	return vector[ranV];
}
inline double randPick(std::vector<double> vector)
{
	double ranV = randRange(0, vector.size());
	return vector[ranV];
}
inline float randPick(std::vector<float> vector)
{
	float ranV = randRange(0, vector.size());
	return vector[ranV];
}

#endif