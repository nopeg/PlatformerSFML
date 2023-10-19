#ifndef Scene_H
#define Scene_H

#include "Camera.h"

enum sceneName { none, title, menu, game };

class Scene
{
protected:
	std::stack<Scene*>* SceneStack;
	RenderWindow* window;
	Event* gameEvent;
	Camera cam;

	Vector2f windowSize;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2f mousePosPrev;

public:
	bool leftApp = false;
	bool leftScene = false;
	sceneName nextScene = none;

	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;

	Scene(std::stack<Scene*>* SceneStack, RenderWindow* window, Event* gameEvent, Camera cam)
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

	virtual ~Scene()
	{

	}

	void exitApp()
	{
		leftApp = true;
	}

	void exitScene()
	{
		leftScene = true;
	}

	void goToScene(sceneName name)
	{
		nextScene = name;
	}

	void updateMousePosition()
	{
		mousePosWindow = Mouse::getPosition(*window);
		mousePosView = window->mapPixelToCoords(mousePosWindow);
	}
};
#endif