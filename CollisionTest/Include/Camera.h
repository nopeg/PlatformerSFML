#ifndef CAMERA_H
#define CAMERA_H

//класс камеры, для удобного управления вида
class Camera
{
private:
	//параметры камеры
	float viewZoom = 1.0;
	float zoomSpeed = 0.05;
	float zoomMax = 2;
	float speed = 0.5;
	float rotation = 0.0f;

	Vector2f shakeOffset;
	/*Vector2f posDist;
	float posAngle = 0.0;*/

public:
	//переменные
	bool canZoom = false;
	View mainView;
	CircleShape shape;

	//функции
	void set(RenderWindow* window, Vector2f pos);
	void move(Vector2f pos, Vector2f prevPos);
	void randShake(float force);
	void resetRotation();
	void updateWindow(RenderWindow* window);
	void updateEvent(Event* gameEvent);

};
#endif