#include "Common.h"
#include "Camera.h"

//настройка камеры
void Camera::set(RenderWindow* window, Vector2f pos)
{
	viewZoom = 1;
	mainView.zoom(1);
	mainView.setRotation(0);
	mainView.setSize({
		static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y) });

	//настройка визуального отображения камеры
	shape.setRadius(4);
	shape.setOrigin({ shape.getRadius(), shape.getRadius() });
	shape.setFillColor(Color::Green);
	shape.setPosition(pos);
}

//передвижение
void Camera::move(Vector2f prevPos, Vector2f newPos)
{
	/*posDist.x = distance({ newPos.x, 0 }, { prevPos.x, 0 });
	posDist.y = distance({ 0, newPos.y }, { 0, prevPos.y });
	posAngle = angle(newPos, prevPos);*/

	shape.move((newPos - prevPos) * speed);
}

//тряска камеры
void Camera::randShake(float force)
{
	mainView.rotate(randPick<int>({ -1, 1 }) * force);
	shakeOffset.x += randPick<int>({ -1, 1 }) * force;
	shakeOffset.y += randPick<int>({ -1, 1 }) * force;
}

//установка изначальных параметров после тряски
void Camera::resetRotation()
{
	mainView.rotate(-1 * mainView.getRotation());
	shakeOffset = lerp2f(shakeOffset, { 0,0 }, 0.8f);
}

//обновления вида окна 
void Camera::updateWindow(RenderWindow* window)
{
	mainView.setCenter(0, 0);
	mainView.move(shape.getPosition() + shakeOffset);
	window->setView(mainView);
}

//обновление событий
void Camera::updateEvent(Event* gameEvent)
{
	//установка нулевого приближения камеры при изменении размеров окна
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

	//приближение и удаление камеры на колесико мышки
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