#ifndef APPLICATION_H
#define APPLICATION_H

#include "Menu.h"
#include "Game.h"
#include "TitleScreen.h"

class Application
{
private:
	//переменные окна
	RenderWindow* window;
	Event* gameEvent;
	Camera cam;
	Clock dtClock;
	float dt;

	//стек игровых сцен
	std::stack<Scene*> SceneStack;

	//функции при инициализации
	void startWindow();
	void startScenes();

public:
	//конструктор деструктор
	Application();
	virtual ~Application();

	//общие функции класса приложения
	void run();
	void update();
	void updateDelta();
	void updateEvent();
	void render();
};

#endif