#include "Common.h"
#include "Application.h"

//создание окна
void Application::startWindow()
{
    //загрузка настроек окна из файла
    std::ifstream ifs("Resources/files/window.ini");
    std::string title = "Title";
    unsigned fLimit = 30;
    bool vSync = false;
    VideoMode windowSize(320, 320);

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> windowSize.width >> windowSize.height;
        ifs >> fLimit;
        ifs >> vSync;
    }
    ifs.close();

    //создание окна с заданными настройками
    window = new RenderWindow(windowSize, title);
    window->setFramerateLimit(fLimit);
    window->setVerticalSyncEnabled(vSync);
    gameEvent = new Event;
}

//добавление сцены начального экрана при запуске приложения
void Application::startScenes()
{
    SceneStack.push(new TitleScreen(&SceneStack, window, gameEvent, &cam));
}


//конструктор
Application::Application()
{
    startWindow();
    startScenes();
}

//деструктор
Application::~Application()
{
    //удаление указателей
    delete window;
    delete gameEvent;

    //удаление последней сцены
    while (!SceneStack.empty())
    {
        delete SceneStack.top();
        SceneStack.pop();
    }
}

//обновление приложения
void Application::run()
{
    while (window->isOpen())
    {
        updateDelta();
        update();
        updateEvent();
        render();
    }
}

//обновление дельта времени (разница времени между кадрами)
void Application::updateDelta()
{
    dt = dtClock.restart().asSeconds();
}

//обновление системы сцен
void Application::update()
{
    if (!SceneStack.empty())
    {
        //обновление сцены
        SceneStack.top()->update(dt);

        //когда сцена меняется
        if (SceneStack.top()->nextScene != none)
        {
            //берем значение переменной nextScene данной сцены и меняем сцену
            sceneName nextScene = SceneStack.top()->nextScene;
            if (SceneStack.top()->leftScene)
            {
                delete SceneStack.top();
                SceneStack.pop();
            }

            switch (nextScene)
            {
            case title:
                SceneStack.push(new TitleScreen(&SceneStack, window, gameEvent, &cam));
                break;
            case menu:
                SceneStack.push(new Menu(&SceneStack, window, gameEvent, &cam));
                break;
            case game:
                SceneStack.push(new Game(&SceneStack, window, gameEvent, &cam));
                break;
            }
        }

        //когда выходим из сцены
        else if (SceneStack.top()->leftScene)
        {
            delete SceneStack.top();
            SceneStack.pop();
        }
    }
}

//обновляем события SFML
void Application::updateEvent()
{
    while (window->pollEvent(*gameEvent))
    {
        //обновляем события сцены
        SceneStack.top()->updateEvent(dt);

        //если окно закрывается завершаем приложение
        if (gameEvent->type == Event::Closed || SceneStack.top()->leftApp)
        {
            delete SceneStack.top();
            SceneStack.pop();

            std::cout << "end game" << std::endl;
            window->close();
        }
    }
}

//отображение графических объектов приложения
void Application::render()
{
    window->clear();

    //берем объекты данной сцены
    if (!SceneStack.empty())
    {
        SceneStack.top()->render();
    }

    window->display();
}