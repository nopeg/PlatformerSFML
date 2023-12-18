#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "UniformGrid.h"
#include "Button.h"
#include "NewShapes.h"


class Game : public Scene
{
private:
	UniGrid ugrid;
	RectangleShape background;
	Font fontPixel;
	Player player;
	std::vector<Entity*> entities;
	std::vector<Enemy> enemies;

	//grid tiles
	Sprite tileSprite;
	Sprite parallaxSprite;

	Font arial;
	Texture button;
	Texture tileTexture;
	Texture parallaxTexture;
	Texture playerTexture;
	Texture enemyTexture;

	Text hp;
	Button gridButton;

	View guiView;

public:

	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera* cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }
		if (!parallaxTexture.loadFromFile("Resources/Images/clouds.png")) { /*error*/ }
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png")) { /*error*/ }
		if (!enemyTexture.loadFromFile("Resources/Images/enemy.png")) { /*error*/ }
		if (!playerTexture.loadFromFile("Resources/Images/player.png")) { /*error*/ }

		print("entered game");

		ugrid.createGrid();

		cam->canZoom = true;
		cam->set(window, { 100, 0 });

		hp = newText({ 0,0 }, arial, std::to_string(int(player.health)), 32, 2, Color::White, Color::Black);

		gridButton.value = false;
		gridButton.set({ window->getView().getCenter().x, window->getView().getCenter().y - window->getSize().y / 2 + 96 }, { 160, 64 });
		gridButton.setTexture(button);
		gridButton.setText(arial, "grid");

		background.setOrigin(Vector2f(window->getSize()) * 4.0f);
		background.setFillColor(Color(180, 200, 220));
		background.setSize(Vector2f(window->getSize()) * 8.0f);

		parallaxSprite.setOrigin(Vector2f(window->getSize()));
		FloatRect fBoundsP(0, 0, window->getSize().x * 2.0f, window->getSize().y * 2.0f);
		IntRect iBoundsP(fBoundsP);
		parallaxSprite.setTexture(parallaxTexture);
		parallaxSprite.setTextureRect(iBoundsP);
		parallaxTexture.setRepeated(true);
		parallaxSprite.setScale(8, 8);

		//grid tiles
		FloatRect fBounds(0, 0, 32 * ugrid.width, 32 * ugrid.height);
		IntRect iBounds(fBounds);
		tileSprite.setTexture(tileTexture);
		tileSprite.setTextureRect(iBounds);
		tileSprite.setScale(ugrid.cellSize / 32, ugrid.cellSize / 32);
		tileTexture.setRepeated(true);

		Entity* body1 = new Entity(ugrid, { 0, 240 });
		body1->setSize({ 2160,32 });
		body1->checkCell(ugrid);
		entities.push_back(body1);

		Enemy enemy(ugrid, { 32,32 },
			{ 0,0 },
			&enemyTexture, Vector2u(3, 1), 0.25f);
		entities.push_back(enemy.body);
		enemies.push_back(enemy);

		for (int i = 0; i < 16; i++)
		{
			Enemy enemy(ugrid, { 32,32 }, 
				{ randRangeF(0, ugrid.cellSize * ugrid.width), randRangeF(0, ugrid.cellSize * ugrid.height) }, 
				&enemyTexture, Vector2u(3, 1), 0.25f);
			entities.push_back(enemy.body);
			enemies.push_back(enemy);

			Entity* bodyi = new Entity(ugrid, { randRangeF(0, ugrid.cellSize * ugrid.width),
				randRangeF(0, ugrid.cellSize * ugrid.height) });
			entities.push_back(bodyi);
		}

		player.set(ugrid, { 32,64 }, { 0,0 }, &playerTexture, Vector2u(3, 3), 0.3f);
		entities.push_back(player.body);

		guiView.zoom(1);
		guiView.setSize({
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y) });
		guiView.setCenter(0, 0);
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
				Enemy enemy(ugrid, { 32,32 }, mousePosView, &enemyTexture, Vector2u(3, 1), 0.25f);
				entities.push_back(enemy.body);
				enemies.push_back(enemy);
			}

			if (gameEvent->mouseButton.button == Mouse::Left)
			{
				Entity* body = new Entity(ugrid, mousePosView);
				entities.push_back(body);
			}
		}

		cam->updateEvent(gameEvent);
	}

	void update(const float& dt)
	{
		player.update(dt, ugrid);
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].update(dt, ugrid, &player);
		}
		cam->move(cam->shape.getPosition(), player.body->getPosition());
		background.setPosition(player.body->getPosition());
		parallaxSprite.setPosition(player.body->getPosition() * 0.2f);

		hp.setPosition({ window->getView().getCenter().x, window->getView().getCenter().y - window->getSize().y / 2 + 96 });
		hp.setString(std::to_string(int(player.health)));

		if (player.health <= 0.0f)
		{
			goToScene(menu);
			exitScene();
		}
	}

	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		cam->updateWindow(window);
		updateMousePosition();

		target->draw(background);
		target->draw(parallaxSprite);
		target->draw(tileSprite);
		for (size_t i = 0; i < entities.size(); i++)
		{
			target->draw(*entities[i]);
		}
		target->draw(cam->shape);

		target->setView(guiView);
		target->draw(hp);
	}
};

#endif