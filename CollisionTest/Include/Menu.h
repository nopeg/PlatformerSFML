#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "Button.h"

//наследуем класс сцены
class Menu : public Scene
{
private:
	//графические объекты сцены
	Button startButton;
	Button optionsButton;
	Button levelEditorButton;
	Button exitButton;
	RectangleShape background;

	//внешние ресурсы
	Font arial;
	Texture button;
	Texture tileTexture;
	Texture parallaxTexture;
	Texture playerTexture;
	Texture enemyTexture;

	//функция для открытия текстового файла в блокноте
	void openFile(std::string name)
	{
		std::ifstream ifs(name);
		std::ofstream ofs;

		//если файл существует
		if (ifs)
		{
			name = "notepad \"" + name + "\"";
			system(name.c_str());
			levelEditorButton.value = false;
			ofs.close();
			ifs.close();
		}
		else
		{
			ofs.open(name);
		}
	}

public:
	Menu(std::stack<Scene*>* Scenes, RenderWindow* window, Event* gameEvent, Camera* cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		//подгрузка ресурсов
		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }
		if (!parallaxTexture.loadFromFile("Resources/Images/clouds.png")) { /*error*/ }
		if (!tileTexture.loadFromFile("Resources/Images/Tile1.png")) { /*error*/ }
		if (!enemyTexture.loadFromFile("Resources/Images/enemy.png")) { /*error*/ }
		if (!playerTexture.loadFromFile("Resources/Images/player.png")) { /*error*/ }

		std::cout << "entered menu" << std::endl;

		//настройка камеры
		cam->canZoom = false;
		cam->set(window, {windowSize.x / 2, windowSize.y / 2});

		background.setPosition({ 0, 0 });
		background.setFillColor(Color(250, 240, 230));
		background.setSize(windowSize);

		//настройка кнопок
		startButton.value = false;
		startButton.set({ windowSize.x / 2, windowSize.y / 2 - 128 }, { 160, 64 });
		startButton.setTexture(button);
		startButton.setText(arial, "start game");

		levelEditorButton.value = false;
		levelEditorButton.set({ windowSize.x / 2, windowSize.y / 2 - 32 }, { 168, 64 });
		levelEditorButton.setTexture(button);
		levelEditorButton.setText(arial, "level editor");

		optionsButton.value = false;
		optionsButton.set({ windowSize.x / 2, windowSize.y / 2 + 64 }, { 112, 64 });
		optionsButton.setTexture(button);
		optionsButton.setText(arial, "options");

		exitButton.value = false;
		exitButton.set({ windowSize.x / 2, windowSize.y / 2 + 160 }, { 64, 64 });
		exitButton.setTexture(button);
		exitButton.setText(arial, "exit");
	}

	~Menu()
	{
		std::cout << "left menu" << std::endl;
	}

	//обновление событий
	void updateEvent(const float& dt)
	{
		//кнопка "играть"
		startButton.updateToggle(mousePosView, gameEvent);
		if (startButton.value == true)
		{
			goToScene(game);
			exitScene();
		}

		//кнопка "редактор уровня"
		levelEditorButton.updateHold(mousePosView, gameEvent);
		if (levelEditorButton.value == true)
		{
			std::cout << "no proper editor yet" << std::endl;

			openFile("Resources/files/world.ini");
		}

		//кнопка "настройки"
		optionsButton.updateHold(mousePosView, gameEvent);
		if (optionsButton.value == true)
		{
			std::cout << "no proper options yet" << std::endl;

			openFile("Resources/files/window.ini");
		}

		//кнопка "выход"
		exitButton.updateToggle(mousePosView, gameEvent);
		if (exitButton.value == true)
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
		startButton.render(target);
		levelEditorButton.render(target);
		optionsButton.render(target);
		exitButton.render(target);
	}
};

#endif