#ifndef BUTTON_H
#define BUTTON_H

//класс кнопки
class Button
{
private:
    //параметры кнопки
    bool mouseClick = true;
    int time = 35;
    int countHold = time;
    int countValue = 32;

    void setColor(Color color);

public:
    //переменные кнопки
    RectangleShape shape;
    Text text;
    bool value = false;
    bool active = true;

    //конструкторы
    Button();
    Button(Vector2f position, Vector2f bounds);
    Button(const Texture& texture, Vector2f position, Vector2f bounds);

    //функции
    void set(Vector2f position, Vector2f bounds);
    void setTexture(const Texture& texture);
    void setText(const Font& font, const std::string& string);
    bool updateToggle(Vector2f mousePos, Event* event);
    bool updateHold(Vector2f mousePos, Event* event);
    void render(RenderTarget* target);
};

#endif