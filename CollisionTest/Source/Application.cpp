#include "Common.h"
#include "Application.h"

//�������� ����
void Application::startWindow()
{
    //�������� �������� ���� �� �����
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

    //�������� ���� � ��������� �����������
    window = new RenderWindow(windowSize, title);
    window->setFramerateLimit(fLimit);
    window->setVerticalSyncEnabled(vSync);
    gameEvent = new Event;
}

//���������� ����� ���������� ������ ��� ������� ����������
void Application::startScenes()
{
    SceneStack.push(new TitleScreen(&SceneStack, window, gameEvent, &cam));
}


//�����������
Application::Application()
{
    startWindow();
    startScenes();
}

//����������
Application::~Application()
{
    //�������� ����������
    delete window;
    delete gameEvent;

    //�������� ��������� �����
    while (!SceneStack.empty())
    {
        delete SceneStack.top();
        SceneStack.pop();
    }
}

//���������� ����������
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

//���������� ������ ������� (������� ������� ����� �������)
void Application::updateDelta()
{
    dt = dtClock.restart().asSeconds();
}

//���������� ������� ����
void Application::update()
{
    if (!SceneStack.empty())
    {
        //���������� �����
        SceneStack.top()->update(dt);

        //����� ����� ��������
        if (SceneStack.top()->nextScene != none)
        {
            //����� �������� ���������� nextScene ������ ����� � ������ �����
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

        //����� ������� �� �����
        else if (SceneStack.top()->leftScene)
        {
            delete SceneStack.top();
            SceneStack.pop();
        }
    }
}

//��������� ������� SFML
void Application::updateEvent()
{
    while (window->pollEvent(*gameEvent))
    {
        //��������� ������� �����
        SceneStack.top()->updateEvent(dt);

        //���� ���� ����������� ��������� ����������
        if (gameEvent->type == Event::Closed || SceneStack.top()->leftApp)
        {
            delete SceneStack.top();
            SceneStack.pop();

            std::cout << "end game" << std::endl;
            window->close();
        }
    }
}

//����������� ����������� �������� ����������
void Application::render()
{
    window->clear();

    //����� ������� ������ �����
    if (!SceneStack.empty())
    {
        SceneStack.top()->render();
    }

    window->display();
}