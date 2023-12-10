#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "Button.h"

class Menu : public Scene
{
private:
	Font arial;
	Texture button;
	Button startButton;
	Button optionsButton;
	Button levelEditorButton;
	Button exitButton;
	RectangleShape background;

public:
	Menu(std::stack<Scene*>* Scenes, RenderWindow* window, Event* gameEvent, Camera cam)
		: Scene(Scenes, window, gameEvent, cam)
	{
		print("entered menu");

		if (!arial.loadFromFile("Resources/fonts/arial.ttf")) { /*error*/ }
		if (!button.loadFromFile("Resources/images/button.png")) { /*error*/ }

		this->cam.canZoom = false;
		this->cam.set(window, {windowSize.x / 2, windowSize.y / 2});

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

		background.setPosition({ 0, 0 });
		background.setFillColor(Color(250, 240, 230));
		background.setSize(windowSize);
	}

	~Menu()
	{
		print("left menu");
	}

	void updateKeybinds(const float& dt)
	{
		startButton.updateToggle(mousePosView, gameEvent);
		if (startButton.value == true)
		{
			goToScene(game);
			exitScene();
		}

		levelEditorButton.updateHold(mousePosView, gameEvent);
		if (levelEditorButton.value == true)
		{
			print("no editor yet");
		}

		optionsButton.updateHold(mousePosView, gameEvent);
		if (optionsButton.value == true)
		{
			print("no options yet");
		}

		exitButton.updateToggle(mousePosView, gameEvent);
		if (exitButton.value == true)
		{
			exitApp();
		}
	}

	void update(const float& dt)
	{
		updateKeybinds(dt);
		updateMousePosition();

		cam.updateWindow(window);
		cam.updateEvent(gameEvent);
		window->setView(cam.mainView);
	}

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