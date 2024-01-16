#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	float viewZoom = 1.0;
	float zoomSpeed = 0.05;
	float zoomMax = 2;
	Vector2f posDist;
	float posAngle = 0.0;
	float speed = 0.5;
	float rotation = 0.0f;

	Vector2f shakeOffset;

public:
	bool canZoom = false;
	View mainView;
	CircleShape shape;

	void set(RenderWindow* window, Vector2f pos);
	void move(Vector2f pos, Vector2f prevPos);
	void randShake(float force);
	void resetRotation();
	void updateWindow(RenderWindow* window);
	void updateEvent(Event* gameEvent);

};
#endif