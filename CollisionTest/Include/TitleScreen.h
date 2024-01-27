#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"
#include "NewShapes.h"

//наследуем класс сцены
class TitleScreen : public Scene
{
private:
	//таймер для перехода
	Clock clock;
	int msec;
	//графические объекты
	Text text;
	RectangleShape background;
	//внешние ресурсы
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
		std::cout << "entered title" << std::endl;

		//загрузка ресурсов
		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }
		if (!parallaxTexture.loadFromFile("Resources/Images/clouds.png")) { /*error*/ }
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png")) { /*error*/ }
		if (!enemyTexture.loadFromFile("Resources/Images/enemy.png")) { /*error*/ }
		if (!playerTexture.loadFromFile("Resources/Images/player.png")) { /*error*/ }

		//настройка камеры
		this->cam->canZoom = false;
		this->cam->set(window, { windowSize.x / 2, windowSize.y / 2 });

		//визуал
		text = newText({ windowSize.x / 2, windowSize.y / 2 }, arial, "welcome", 32, 2, Color::White, Color::Black);
		background.setPosition({ 0, 0 });
		background.setFillColor(Color(210, 222, 190));
		background.setSize(windowSize);
	}

	~TitleScreen()
	{
		std::cout << "left title" << std::endl;
	}

	//обновление событий
	void updateEvent(const float& dt)
	{
		//таймер
		msec = static_cast<unsigned int>(clock.getElapsedTime().asMilliseconds());

		//переход
		if (msec >= 1000)
		{
			goToScene(menu);
			exitScene();
		}

		//выход из приложения
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			exitApp();
		}

		cam->updateEvent(gameEvent);
	}

	//обновление функций сцены
	void update(const float& dt)
	{
		updateMousePosition();
		cam->updateWindow(window);
	}

	//отрисовка объектов
	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(background);
		target->draw(text);
	}
};

#endif