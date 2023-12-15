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
	std::vector<Entity*> entities;
	bool leftB = true;
	bool rightB = true;


	//grid tiles
	Texture tileTexture;
	Texture playerTexture;
	Sprite tileSprite;

public:

	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera* cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		print("entered game");

		ugrid.createGrid();

		cam->canZoom = true;
		cam->set(window, { 100, 0 });

		background.setPosition({ 0, 0 });
		background.setFillColor(Color(100, 100, 100));
		background.setSize(windowSize);

		//grid tiles
		FloatRect fBounds(0, 0, 32 * ugrid.width, 32 * ugrid.height);
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png"))
		{
			// error...
		}
		IntRect iBounds(fBounds);
		tileSprite.setTexture(tileTexture);
		tileSprite.setTextureRect(iBounds);
		tileSprite.setScale(ugrid.cellSize / 32, ugrid.cellSize / 32);
		tileTexture.setRepeated(true);

		Entity* body1 = new Entity(ugrid, { 0, 240 });
		body1->setSize({ 2160,32 });
		body1->checkCell(ugrid);
		entities.push_back(body1);

		for (int i = 0; i < 10; i++)
		{
			Entity* bodyi = new Entity(ugrid, { randRangeF(0, ugrid.cellSize * ugrid.width),
				randRangeF(0, ugrid.cellSize * ugrid.height) });
			entities.push_back(bodyi);
		}


		if (!playerTexture.loadFromFile("Resources/Images/player.png"))
		{
			// error...
		}
		player.set(ugrid, { 32,64 }, { 0,0 }, &playerTexture, Vector2u(3, 1), 0.25f);
		entities.push_back(player.body);
	}

	~Game()
	{
		print("left game");
	}

	void updateEvent(const float& dt)
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
				rightB = false;
			}

			if (gameEvent->mouseButton.button == Mouse::Left)
			{
				Entity* body = new Entity(ugrid, mousePosView);
				entities.push_back(body);
				leftB = false;
			}
		}
	}

	void update(const float& dt)
	{
		player.update(dt, ugrid);
		cam->updateEvent(gameEvent);
		cam->updateWindow(window);
		cam->move(cam->shape.getPosition(), player.body->getPosition());

		updateMousePosition();
		
	}

	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(background);
		target->draw(tileSprite);
		for (size_t i = 0; i < entities.size(); i++)
		{
			target->draw(*entities[i]);
		}
		target->draw(cam->shape);
	}
};

#endif