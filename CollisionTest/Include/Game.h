#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "UniformGrid.h"

class Game : public Scene
{
private:
	RectangleShape background;

	Player player;

	std::vector<std::vector<int>> uniGrid;
	float cellSize = 64.0f;
	unsigned int height = 8;
	unsigned int width = 8;

public:

	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		print("entered game");

		this->cam.canZoom = true;
		this->cam.set(window, { 0, 0 });

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

		player.set({ 32,32 }, { 0,0 });
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

		}
	}

	void update(const float& dt)
	{
		updateKeybinds(dt);
		updateMousePosition();

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			print(clamp<int>(int(mousePosView.y / cellSize), 0, height - 1) << clamp<int>(int(mousePosView.x / cellSize), 0, width - 1));
			//print(uniGrid[clamp<int>(int(mousePosView.y / cellSize), 0, height - 1)][clamp<int>(int(mousePosView.x / cellSize), 0, width - 1)]);
		}
		player.update(dt);

		cam.update({ 0,0 }, { 0,0 });
		cam.updateWindow(window);
		cam.updateEvent(gameEvent);
		window->setView(cam.mainView);
	}

	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(background);
		target->draw(cam.shape);
		target->draw(player.shape);
	}
};

#endif