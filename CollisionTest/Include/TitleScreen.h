#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"
#include "NewShapes.h"

class TitleScreen : public Scene
{
private:
	Clock clock;
	int msec;
	Text text;
	RectangleShape background;

	Font arial;
	Texture button;
	Texture tileTexture;
	Texture parallaxTexture;
	Texture playerTexture;
	Texture enemyTexture;

public:
	TitleScreen(std::stack<Scene*>* Scenes, RenderWindow* window, Event* gameEvent, Camera* cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		print("entered title");

		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }
		if (!parallaxTexture.loadFromFile("Resources/Images/clouds.png")) { /*error*/ }
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png")) { /*error*/ }
		if (!enemyTexture.loadFromFile("Resources/Images/enemy.png")) { /*error*/ }
		if (!playerTexture.loadFromFile("Resources/Images/player.png")) { /*error*/ }

		this->cam->canZoom = false;
		this->cam->set(window, { windowSize.x / 2, windowSize.y / 2 });

		text = newText({ windowSize.x / 2, windowSize.y / 2 }, arial, "welcome", 32, 2, Color::White, Color::Black);

		background.setPosition({ 0, 0 });
		background.setFillColor(Color(210, 222, 190));
		background.setSize(windowSize);
	}

	~TitleScreen()
	{
		print("left title");
	}

	void updateEvent(const float& dt)
	{
		msec = static_cast<unsigned int>(clock.getElapsedTime().asMilliseconds());

		if (msec >= 1000)
		{
			goToScene(menu);
			exitScene();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			exitApp();
		}
	}

	void update(const float& dt)
	{
		updateEvent(dt);
		updateMousePosition();

		cam->updateWindow(window);
		cam->updateEvent(gameEvent);
	}

	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(background);
		target->draw(text);
	}
};

#endif