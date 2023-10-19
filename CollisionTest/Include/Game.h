#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"

class Game : public Scene
{
private:
	RectangleShape background;

	std::vector<FloatRect> uniGrid;
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
				FloatRect fr(j * cellSize, i * cellSize, cellSize, cellSize);
				uniGrid.push_back(fr);
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

		for (int i = 0; i < height * width; i++)
		{
			if (uniGrid[i].intersects(player.shape.getGlobalBounds()))
			{
				print(i);
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