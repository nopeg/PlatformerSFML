#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "UniformGrid.h"

class Game : public Scene
{
private:
	UniGrid ugrid;

	RectangleShape background;

	Font fontPixel;
	Player player;
	Camera cam;

	std::vector<Entity*> entities;

public:

	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		print("entered game");

		ugrid.createGrid();

		this->cam.canZoom = true;
		this->cam.set(window, { 100, 0 });

		background.setPosition({ 0, 0 });
		background.setFillColor(Color(100, 100, 100));
		background.setSize(windowSize);

		Entity* body1 = new Entity(ugrid, { 0, 2160 });
		body1->setSize({ 2160,32 });
		body1->checkCell(ugrid);
		entities.push_back(body1);

		for (int i = 0; i < 10; i++)
		{
			Entity* bodyi = new Entity(ugrid, { randRangeF(0, ugrid.cellSize * ugrid.width),
				randRangeF(0, ugrid.cellSize * ugrid.height) });
			entities.push_back(bodyi);
		}

		player.set(ugrid, { 32,64 }, { 0,0 });
		entities.push_back(player.body);
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

		if (gameEvent->type == Event::MouseButtonPressed)
		{
			if (gameEvent->mouseButton.button == Mouse::Right)
			{
				for (int i = 0; i < ugrid.getBodies(mousePosView).size(); i++)
				{
					std::cout << ugrid.getBodies(mousePosView)[i]->id << std::endl;
				}
				std::cout << std::endl;
			}

			if (gameEvent->mouseButton.button == Mouse::Left)
			{
				Entity* body = new Entity(ugrid, mousePosView);
				entities.push_back(body);
			}
		}
	}

	void update(const float& dt)
	{
		updateKeybinds(dt);

		player.update(dt, ugrid);
		cam.updateEvent(gameEvent);
		cam.updateWindow(window);
		cam.move(cam.shape.getPosition(), player.body->getPosition());

		updateMousePosition();
	}

	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(background);
		for (size_t i = 0; i < entities.size(); i++)
		{
			target->draw(*entities[i]);
		}
		target->draw(cam.shape);
	}
};

#endif