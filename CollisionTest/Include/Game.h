#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"

class Game : public Scene
{
private:
	RectangleShape background;

	std::vector<std::vector<int>> uniGrid;
	float cellSize = 128.0f;
	unsigned int height = 8;
	unsigned int width = 8;

public:
	Player player;

	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		print("entered game");

		player.set(Vector2f(16, 32), Vector2f(16, 16));
		player.shape.getGlobalBounds();

		this->cam.canZoom = true;
		this->cam.set(window, player.shape.getPosition());

		background.setPosition({ 0, 0 });
		background.setFillColor(Color(100, 100, 100));
		background.setSize(windowSize);


		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				uniGrid.push_back({ i,j });
			}
		}
	}

	~Game()
	{
		print("left game");
	}

	void updateKeybinds(const float& dt)
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			goToScene(menu);
			exitScene();
		}
		if (gameEvent->type == sf::Event::MouseButtonPressed)
		{
			if (int(player.shape.getGlobalBounds().top / cellSize) < height && player.shape.getGlobalBounds().top >= 0)
			{
				if (int(player.shape.getGlobalBounds().left / cellSize) < width && player.shape.getGlobalBounds().left >= 0)
				{
					print(uniGrid[int(player.shape.getGlobalBounds().left / cellSize)][int(player.shape.getGlobalBounds().top / cellSize)]);
				}
			}
		}
	}

	void update(const float& dt)
	{
		Vector2f prevPlayerPos = player.shape.getPosition();
		updateKeybinds(dt);
		updateMousePosition();

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			print("yep");
		}

		player.update(dt);

		cam.update(player.shape.getPosition(), prevPlayerPos);
		cam.updateWindow(window);
		cam.updateEvent(gameEvent);
		window->setView(cam.mainView);
	}

	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(background);
		target->draw(player.shape);
		target->draw(cam.shape);
	}
};

#endif