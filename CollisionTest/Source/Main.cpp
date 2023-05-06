#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Common.h"
using namespace sf;

static std::vector<RectangleShape> boxV;
void createBox(Vector2f pos, Vector2f bounds, float outWidth, Color colorFill, Color colorOut)
{
    RectangleShape box(bounds);

    box.setOrigin(bounds.x / 2, bounds.y / 2);
    box.setSize(bounds);
    box.setFillColor(colorFill);
    box.setPosition(pos);
    box.setOutlineThickness(outWidth);
    box.setOutlineColor(colorOut);

    boxV.push_back(box);
}

int main()
{
    std::cout << "start" << std::endl;
    std::srand(std::time(nullptr));
    boxV.clear();

    RenderWindow window(VideoMode(320, 320), "Collision Test");
    View view(FloatRect(0.f, 0.f, 320.f, 320.f));
    Event event;

    createBox(Vector2f(32, 32), Vector2f(32, 32), 2, Color(0,0,0,0), Color(255, 255, 255));
    createBox(Vector2f(128, 128), Vector2f(32, 32), 2, Color(0, 0, 0, 0), Color(255, 255, 255));
    createBox(Vector2f(256, 256), Vector2f(32, 32), 2, Color(0, 0, 0, 0), Color(255, 255, 255));

    Vector2f mousePos(0, 0);
    int grab = -1;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            //closing app
            if (event.type == Event::Closed)
            {
                std::cout << "fin" << std::endl;
                window.close();
            }

            //resizing view with window
            if (event.type == Event::Resized)
            {
                view.zoom(1);
                view.setSize({ static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (boxV.size() > 0)
                    {
                        if (grab == -1)
                        {
                            for (size_t i = 0; i < boxV.size(); i++)
                            {
                                if (boxV[i].getGlobalBounds().contains(mousePos))
                                {
                                    grab = i;
                                    std::cout << grab << std::endl;
                                }
                            }
                        }
                        else
                        {
                            grab = -1;
                        }
                    }
                }
            }
        }

        mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (grab >= 0)
        {
            boxV[grab].setPosition(mousePos);
        }

        view.setCenter(160, 160);
        window.setView(view);

        window.clear();
        for (size_t i = 0; i < boxV.size(); i++)
        {
            window.draw(boxV[i]);
        }
        window.display();
    }

    return 0;
}