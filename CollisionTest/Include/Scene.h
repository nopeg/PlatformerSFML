#ifndef Scene_H
#define Scene_H

#include "Camera.h"

//перечисление возможных сцен для перехода
enum sceneName { none, title, menu, game };

class Scene
{
protected:
	//переменные сцены, которые берутся из приложения
	std::stack<Scene*>* SceneStack;
	RenderWindow* window;
	Event* gameEvent;
	Camera* cam;
	Vector2f windowSize;

	//координаты мыши
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2f mousePosPrev;

public:
	//переменные для перехода между сценами
	bool leftApp = false;
	bool leftScene = false;
	sceneName nextScene = none;

	//виртуальные функции
	virtual void updateEvent(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;

	//конструктор и присваивание значений переменным выше
	Scene(std::stack<Scene*>* SceneStack, RenderWindow* window, Event* gameEvent, Camera* cam)
	{
		this->SceneStack = SceneStack;
		this->window = window;
		this->gameEvent = gameEvent;
		this->cam = cam;

		leftApp = false;
		leftScene = false;
		nextScene = none;

		windowSize = 
		{ 
			static_cast<float>(window->getSize().x), 
			static_cast<float>(window->getSize().y) 
		};
	}

	//деструктор
	virtual ~Scene() {}

	//выход из приложения
	void exitApp()
	{
		leftApp = true;
	}

	//выход из сцены
	void exitScene()
	{
		leftScene = true;
	}

	//переход в сцену
	void goToScene(sceneName name)
	{
		nextScene = name;
	}

	//обновление координат мыши
	void updateMousePosition()
	{
		mousePosWindow = Mouse::getPosition(*window);
		mousePosView = window->mapPixelToCoords(mousePosWindow);
	}
};
#endif