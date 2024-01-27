#ifndef GAMESCENE_H
#define GAMESCENE_H

//подключаем файлы заголовков
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "UniformGrid.h"
#include "Button.h"
#include "NewShapes.h"

class Game : public Scene
{
private:
	//игровые объекты
	UniGrid ugrid;
	Player player;
	std::vector<Entity*> entities;
	std::vector<Enemy> enemies;
	objectType inventory = objectType::wall;
	//объекты GUI
	View guiView;
	Text hp;
	//визуал сцены
	Sprite tileSprite;
	Sprite parallaxSprite;
	RectangleShape point;
	RectangleShape background;
	//внешние ресурсы
	Font arial;
	Texture button;
	Texture tileTexture;
	Texture parallaxTexture;
	Texture playerTexture;
	Texture enemyTexture;

	//сохранение мира с позицией игрока
	void saveWorld(Vector2f playerPos)
	{
		std::ofstream ofs("Resources/files/world.ini");

		//сохранение параметров игрока
		ofs << objectType::player << " " << int(playerPos.x) << " " << int(playerPos.y) << std::endl << std::endl;

		//сохранение параметров врагов
		for (int i = 0; i < enemies.size(); i++)
		{
			ofs << objectType::enemy << " " << int(enemies[i].body->getPosition().x)
				<< " " << int(enemies[i].body->getPosition().y) << std::endl;
		}
		ofs << std::endl;

		//сохранение параметров прочих объектов
		for (int i = 0; i < entities.size(); i++)
		{
			//стены
			if (entities[i]->id == objectType::wall)
			{
				ofs << objectType::wall << " " 
					<< int(entities[i]->getPosition().x) << " " << int(entities[i]->getPosition().y) << " " 
					<< int(entities[i]->getSize().x) << " " << int(entities[i]->getSize().y) << std::endl;
			}

			//шипы
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

	//загрузка мира
	void loadWorld()
	{
		std::ifstream ifs("Resources/files/world.ini");
		std::string line;

		entities.clear();
		enemies.clear();

		if (ifs)
		{
			//чтение по строкам
			while (std::getline(ifs, line))
			{
				if (!line.empty())
				{
					//удаление всех символов, кроме цифр и минуса
					removeChars(line);
					std::istringstream ss(line);
					int v;
					std::vector<int> data;
					while (ss >> v)
					{
						data.push_back(v);
					}

					//загрузка объектов по ID в начале строки
					if (data.size() != 0)
					{
						switch (data[0])
						{
							//стены
							case objectType::wall:
								if (data.size() == 5)
								{
									Entity* wall = new Entity(ugrid, Vector2f(data[1], data[2]), 
										Vector2f(data[3], data[4]), objectType::wall);
									entities.push_back(wall);
								}
								break;

							//шипы
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

							//игрок
							case objectType::player:
								if (data.size() == 3)
								{
									player.set(ugrid, { 32,64 }, Vector2f(data[1], data[2]), 
										&playerTexture, Vector2u(3, 3), 0.3f);
									entities.push_back(player.body);
								}
								break;

							//враги
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
			//если не удалось открыть файл мира, создаем пустой с координатами игрока
			saveWorld(Vector2f(0, 0));
			loadWorld();
		}

		ifs.close();
	}


public:
	//конструктор
	Game(std::stack<Scene*>* Scenes, RenderWindow* window, Event *gameEvent, Camera* cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		//загружаем ресурсы
		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }
		if (!parallaxTexture.loadFromFile("Resources/Images/clouds.png")) { /*error*/ }
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png")) { /*error*/ }
		if (!enemyTexture.loadFromFile("Resources/Images/enemy.png")) { /*error*/ }
		if (!playerTexture.loadFromFile("Resources/Images/player.png")) { /*error*/ }

		std::cout << "entered game" << std::endl;

		//создаем решетку физических объектов
		ugrid.createGrid();

		//настройка камеры
		cam->canZoom = true;
		cam->set(window, { 0, 0 });

		//точка в начале координат
		point.setPosition(0, 0);
		point.setSize(Vector2f(16, 16));
		point.setFillColor(Color::Green);

		//текст здоровья игрока
		hp = newText({ 0,0 }, arial, std::to_string(int(player.health)), 32, 2, Color::White, Color::Black);

		//задний фон
		background.setOrigin(Vector2f(window->getSize()) * 4.0f);
		background.setFillColor(Color(180, 200, 220));
		background.setSize(Vector2f(window->getSize()) * 8.0f);

		//параллаксный фон облаков
		parallaxSprite.setOrigin(Vector2f(window->getSize()));
		FloatRect fBoundsP(0, 0, window->getSize().x * 2.0f, window->getSize().y * 2.0f);
		IntRect iBoundsP(fBoundsP);
		parallaxSprite.setTexture(parallaxTexture);
		parallaxSprite.setTextureRect(iBoundsP);
		parallaxTexture.setRepeated(true);
		parallaxSprite.setScale(8, 8);

		//отрисовка физической сетки
		FloatRect fBounds(0, 0, 32 * ugrid.width, 32 * ugrid.height);
		IntRect iBounds(fBounds);
		tileSprite.setTexture(tileTexture);
		tileSprite.setTextureRect(iBounds);
		tileSprite.setScale(ugrid.cellSize / 32, ugrid.cellSize / 32);
		tileTexture.setRepeated(true);

		//полотно элементов GUI
		guiView.zoom(1);
		guiView.setSize({
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y) });
		guiView.setCenter(0, 0);

		//загружаем мир из файла
		loadWorld();
	}

	~Game()
	{
		std::cout << "left game" << std::endl;
	}

	//обновление событий
	void updateEvent(const float& dt)
	{
		//выход в меню
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			goToScene(menu);
			exitScene();
		}

		//сохранение мира
		if (Keyboard::isKeyPressed(Keyboard::Z))
		{
			saveWorld(Vector2f(128, 0));
			std::cout << "saving world" << std::endl;
		}

		//система инвентаря
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

		//создание объекта из инвентаря на нажатие мыши
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

	//главный цикл игры
	void update(const float& dt)
	{
		//если игрок существует в сцене
		if (player.body != nullptr)
		{
			//обновляем игрока и задний фон
			player.update(dt, ugrid, cam);
			background.setPosition(player.body->getPosition());
			parallaxSprite.setPosition(player.body->getPosition() * 0.2f);

			//обновляем врагов
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].update(dt, ugrid, &player);
			}

			//обновляем текст здоровья
			hp.setPosition({ window->getView().getCenter().x, 
				window->getView().getCenter().y - window->getSize().y / 2 + 96 });
			hp.setString(std::to_string(int(player.health)));

			//при смерти выходим в меню
			if (player.health <= 0.0f)
			{
				goToScene(menu);
				exitScene();
			}
		}

		cam->updateWindow(window);
		updateMousePosition();
	}

	//отрисовка
	void render(RenderTarget* target)
	{
		if (!target)
			target = this->window;

		//объекты мира
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