#include "Common.h"
#include "NewShapes.h"
#include "Button.h"

Button::Button() {}
Button::Button(Vector2f position, Vector2f bounds)
{
    set(position, bounds);
}
Button::Button(const Texture& texture, Vector2f position, Vector2f bounds)
{
    set(position, bounds);
    setTexture(texture);
}

void Button::set(Vector2f position, Vector2f bounds)
{
    shape = newBox(bounds, position, 0, colorOff, Color::White);
}

void Button::setTexture(const Texture& texture)
{
    shape.setTexture(&texture);
}

void Button::setText(const Font& font, const std::string& string)
{
    Vector2f textPos = shape.getPosition();
    text = newText(textPos, font, string, shape.getSize().y / 2, 2, Color::White, Color::Black);
    text.setPosition(textPos);
}

void Button::setColor(Color color)
{
    shape.setFillColor(color);
    text.setFillColor(color);
}

bool Button::updateToggle(Vector2f mousePos, Event* event)
{
    if ((shape.getGlobalBounds().contains(mousePos) || 
        text.getGlobalBounds().contains(mousePos)) && active == true)
    {
        if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
        {
            if (mouseClick)
            {
                if (value)
                {
                    setColor(colorOff);
                    value = false;
                }
                else
                {
                    setColor(colorOn);
                    value = true;
                }
                mouseClick = false;
            }
        }
        else
        {
            if (value)
            {
                setColor(colorEnterOn);
            }
            else
            {
                setColor(colorEnterOff);
            }
            mouseClick = true;
        }
    }
    else
    {
        if (value)
        {
            setColor(colorOn);
        }
        else
        {
            if (active)
            {
                setColor(colorOff);
            }
            else
            {
                setColor(colorDisabled);
            }
        }
    }
    return value;
}

bool Button::updateHold(Vector2f mousePos, Event* event)
{
    if ((shape.getGlobalBounds().contains(mousePos) || 
        text.getGlobalBounds().contains(mousePos)) && active == true)
    {
        if (event->type == Event::MouseButtonPressed)
        {
            countHold++;
            if (countValue < time - 1)
            {
                countValue++;
            }
            setColor(colorOn);
            if (countHold >= time + 1 - countValue)
            {
                value = true;
                countHold = 0;
            }
            else
            {
                value = false;
            }
        }
        if (event->type == Event::MouseButtonReleased)
        {
            countHold = time;
            countValue = 0;
            setColor(colorOff);
            value = false;
        }

        if (shape.getFillColor() == Color(colorOff))
        {
            value = false;
            setColor(Color(colorEnterOff));
        }
    }
    else
    {
        if (active == true)
        {
            setColor(Color(colorOff));
        }
        else
        {
            setColor(colorDisabled);
        }
        value = false;
    }
    return value;
}

void Button::render(RenderTarget* target)
{
    target->draw(shape);
    target->draw(text);
}
