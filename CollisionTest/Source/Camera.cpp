#include "Common.h"
#include "Camera.h"

void Camera::set(RenderWindow* window, Vector2f pos)
{
	viewZoom = 1;
	mainView.zoom(1);
	mainView.setRotation(0);
	mainView.setSize({
		static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y) });

	shape.setRadius(4);
	shape.setOrigin({ shape.getRadius(), shape.getRadius() });
	shape.setFillColor(Color::Green);
	shape.setPosition(pos);
}

void Camera::move(Vector2f prevPos, Vector2f newPos)
{
	posDist.x = distance({ newPos.x, 0 }, { prevPos.x, 0 });
	posDist.y = distance({ 0, newPos.y }, { 0, prevPos.y });
	posAngle = angle(newPos, prevPos);

	shape.move((newPos - prevPos) * speed);
}

void Camera::randShake(float force)
{
	mainView.rotate(randPick<int>({ -1, 1 }) * force);
	shakeOffset.x += randPick<int>({ -1, 1 }) * force;
	shakeOffset.y += randPick<int>({ -1, 1 }) * force;
}

void Camera::resetRotation()
{
	mainView.rotate(-1 * mainView.getRotation());
	shakeOffset = interpolate(shakeOffset, { 0,0 }, 0.8f);
}


void Camera::updateWindow(RenderWindow* window)
{
	mainView.setCenter(0, 0);
	mainView.move(shape.getPosition() + shakeOffset);
	window->setView(mainView);
}

void Camera::updateEvent(Event* gameEvent)
{
	//resizing view with window
	if (gameEvent->type == Event::Resized)
	{
		viewZoom = 1;
		mainView.zoom(1);
		Vector2f viewSize =
		{
			static_cast<float>(gameEvent->size.width),
			static_cast<float>(gameEvent->size.height)
		};
		mainView.setSize(viewSize);
		mainView.setRotation(rotation);
	}

	//zoom view mouse wheel
	if (canZoom)
	{
		if (gameEvent->type == Event::MouseWheelMoved)
		{
			if (gameEvent->mouseWheel.delta < 0)
			{
				if (viewZoom < 1 + zoomMax)
				{
					mainView.zoom(1 + zoomSpeed);
					viewZoom += zoomSpeed;
				}
			}
			if (gameEvent->mouseWheel.delta > 0)
			{
				if (viewZoom > 1 - zoomMax)
				{
					mainView.zoom(1 - zoomSpeed);
					viewZoom -= zoomSpeed;
				}
			}
		}
	}
}