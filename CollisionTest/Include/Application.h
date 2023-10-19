#ifndef APPLICATION_H
#define APPLICATION_H

#include "Menu.h"
#include "Game.h"
#include "TitleScreen.h"

class Application
{
private:
	RenderWindow* window;
	Event* gameEvent;
	Camera cam;
	Clock dtClock;
	float dt;

	std::stack<Scene*> SceneStack;

	void startWindow();
	void startScenes();

public:
	Application();
	virtual ~Application();

	void run();
	void update();
	void updateDelta();
	void updateEvent();
	void render();
};

#endif