#ifndef GAMESCENE_H
#define GAMESCENE_H

//���������� ����� ����������
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "UniformGrid.h"
#include "Button.h"
#include "NewShapes.h"

class Game : public Scene
{
private:
	//������� �������
	UniGrid ugrid;
	Player player;
	std::vector<Entity*> entities;
	std::vector<Enemy> enemies;
	objectType inventory = objectType::wall;
	//������� GUI
	View guiView;
	Text hp;
	//������ �����
	Sprite tileSprite;
	Sprite parallaxSprite;
	RectangleShape point;
	RectangleShape background;
	//������� �������
	Font arial;
	Texture button;
	Texture tileTexture;
	Texture parallaxTexture;
	Texture playerTexture;
	Texture enemyTexture;

	//���������� ���� � �������� ������
	void saveWorld(Vector2f playerPos)
	{
		std::ofstream ofs("Resources/files/world.ini");

		//���������� ���������� ������
		ofs << objectType::player << " " << int(playerPos.x) << " " << int(playerPos.y) << std::endl << std::endl;

		//���������� ���������� ������
		for (int i = 0; i < enemies.size(); i++)
		{
			ofs << objectType::enemy << " " << int(enemies[i].body->getPosition().x)
				<< " " << int(enemies[i].body->getPosition().y) << std::endl;
		}
		ofs << std::endl;

		//���������� ���������� ������ ��������
		for (int i = 0; i < entities.size(); i++)
		{
			//�����
			if (entities[i]->id == objectType::wall)
			{
				ofs << objectType::wall << " " 
					<< int(entities[i]->getPosition().x) << " " << int(entities[i]->getPosition().y) << " " 
					<< int(entities[i]->getSize().x) << " " << int(entities[i]->getSize().y) << std::endl;
			}

			//����
			if (entities[i]->id == objectType::spikes)
			{
				ofs << objectType::spikes << " "
					<< int(entities[i]->getPosition().x) << " " << int(entities[i]->getPosition().y) << " "
					<< int(entities[i]->getSize().x) << " " << int(entities[i]->getSize().y) << std::endl;
			}
		}
		ofs << std::endl;

		ofs.close();
	}

	//�������� ����
	void loadWorld()
	{
		std::ifstream ifs("Resources/files/world.ini");
		std::string line;

		entities.clear();
		enemies.clear();

		if (ifs)
		{
			//������ �� �������
			while (std::getline(ifs, line))
			{
				if (!line.empty())
				{
					//�������� ���� ��������, ����� ���� � ������
					removeChars(line);
					std::istringstream ss(line);
					int v;
					std::vector<int> data;
					while (ss >> v)
					{
						data.push_back(v);
					}

					//�������� �������� �� ID � ������ ������
					if (data.size() != 0)
					{
						switch (data[0])
						{
							//�����
							case objectType::wall:
								if (data.size() == 5)
								{
									Entity* wall = new Entity(ugrid, Vector2f(data[1], data[2]), 
										Vector2f(data[3], data[4]), objectType::wall);
									entities.push_back(wall);
								}
								break;

							//����
							case objectType::spikes:
								if (data.size() == 5)
								{
								
									Entity* spikes = new Entity(ugrid, Vector2f(data[1], data[2]),
										Vector2f(data[3], data[4]), objectType::spikes);
									spikes->setFillColor(Color::Red);
									spikes->setOutlineThickness(0);
									entities.push_back(spikes);
								}
								break;

							//�����
							case objectType::player:
								if (data.size() == 3)
								{
									player.set(ugrid, { 32,64 }, Vector2f(data[1], data[2]), 
										&playerTexture, Vector2u(3, 3), 0.3f);
									entities.push_back(player.body);
								}
								break;

							//�����
							case objectType::enemy:
								if (data.size() == 3)
								{
									Enemy enemy(ugrid, { 32,32 }, Vector2f(data[1], data[2]), 
										&enemyTexture, Vector2u(3, 1), 0.25f);
									entities.push_back(enemy.body);
									enemies.push_back(enemy);
								}
								break;
						}
					}
				}
			}
		}
		else
		{
			//���� �� ������� ������� ���� ����, ������� ������ � ������������ ������
			saveWorld(Vector2f(0, 0));
			loadWorld();
		}

		ifs.close();
	}


public:
	//�����������
	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera* cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		//��������� �������
		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }
		if (!parallaxTexture.loadFromFile("Resources/Images/clouds.png")) { /*error*/ }
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png")) { /*error*/ }
		if (!enemyTexture.loadFromFile("Resources/Images/enemy.png")) { /*error*/ }
		if (!playerTexture.loadFromFile("Resources/Images/player.png")) { /*error*/ }

		std::cout << "entered game" << std::endl;

		//������� ������� ���������� ��������
		ugrid.createGrid();

		//��������� ������
		cam->canZoom = true;
		cam->set(window, { 0, 0 });

		//����� � ������ ���������
		point.setPosition(0, 0);
		point.setSize(Vector2f(16, 16));
		point.setFillColor(Color::Green);

		//����� �������� ������
		hp = newText({ 0,0 }, arial, std::to_string(int(player.health)), 32, 2, Color::White, Color::Black);

		//������ ���
		background.setOrigin(Vector2f(window->getSize()) * 4.0f);
		background.setFillColor(Color(180, 200, 220));
		background.setSize(Vector2f(window->getSize()) * 8.0f);

		//������������ ��� �������
		parallaxSprite.setOrigin(Vector2f(window->getSize()));
		FloatRect fBoundsP(0, 0, window->getSize().x * 2.0f, window->getSize().y * 2.0f);
		IntRect iBoundsP(fBoundsP);
		parallaxSprite.setTexture(parallaxTexture);
		parallaxSprite.setTextureRect(iBoundsP);
		parallaxTexture.setRepeated(true);
		parallaxSprite.setScale(8, 8);

		//��������� ���������� �����
		FloatRect fBounds(0, 0, 32 * ugrid.width, 32 * ugrid.height);
		IntRect iBounds(fBounds);
		tileSprite.setTexture(tileTexture);
		tileSprite.setTextureRect(iBounds);
		tileSprite.setScale(ugrid.cellSize / 32, ugrid.cellSize / 32);
		tileTexture.setRepeated(true);

		//������� ��������� GUI
		guiView.zoom(1);
		guiView.setSize({
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y) });
		guiView.setCenter(0, 0);

		//��������� ��� �� �����
		loadWorld();
	}

	~Game()
	{
		std::cout << "left game" << std::endl;
	}

	//���������� �������
	void updateEvent(const float& dt)
	{
		//����� � ����
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			goToScene(menu);
			exitScene();
		}

		//���������� ����
		if (Keyboard::isKeyPressed(Keyboard::Z))
		{
			saveWorld(Vector2f(128, 0));
			std::cout << "saving world" << std::endl;
		}

		//������� ���������
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			inventory = objectType::wall;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			inventory = objectType::spikes;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			inventory = objectType::enemy;
		}

		//�������� ������� �� ��������� �� ������� ����
		if (gameEvent->type == Event::MouseButtonPressed)
		{
			if (gameEvent->mouseButton.button == Mouse::Left)
			{
				if (inventory == objectType::wall)
				{
					Entity* wall = new Entity(ugrid, mousePosView,
						Vector2f(randRangeF(32, 320), randRangeF(32, 320)), objectType::wall);
					entities.push_back(wall);
				}

				if (inventory == objectType::spikes)
				{
					Entity* spikes = new Entity(ugrid, mousePosView,
						Vector2f(32, 32), objectType::spikes);
					spikes->setFillColor(Color::Red);
					spikes->setOutlineThickness(0);
					entities.push_back(spikes);
				}

				if (inventory == objectType::enemy)
				{
					Enemy enemy(ugrid, { 32,32 }, mousePosView, &enemyTexture, Vector2u(3, 1), 0.25f);
					entities.push_back(enemy.body);
					enemies.push_back(enemy);
				}
			}
		}

		cam->updateEvent(gameEvent);
	}

	//������� ���� ����
	void update(const float& dt)
	{
		//���� ����� ���������� � �����
		if (player.body != nullptr)
		{
			//��������� ������ � ������ ���
			player.update(dt, ugrid, cam);
			background.setPosition(player.body->getPosition());
			parallaxSprite.setPosition(player.body->getPosition() * 0.2f);

			//��������� ������
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].update(dt, ugrid, &player);
			}

			//��������� ����� ��������
			hp.setPosition({ window->getView().getCenter().x, 
				window->getView().getCenter().y - window->getSize().y / 2 + 96 });
			hp.setString(std::to_string(int(player.health)));

			//��� ������ ������� � ����
			if (player.health <= 0.0f)
			{
				goToScene(menu);
				exitScene();
			}
		}

		cam->updateWindow(window);
		updateMousePosition();
	}

	//���������
	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		//������� ����
		target->draw(background);
		target->draw(parallaxSprite);
		target->draw(tileSprite);
		for (size_t i = 0; i < entities.size(); i++)
		{
			target->draw(*entities[i]);
		}
		target->draw(point);

		//GUI
		if (player.body != nullptr)
		{
			target->draw(cam->shape);

			target->setView(guiView);
			target->draw(hp);
		}
	}
};

#endif