#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
    bool mouseClick = true;
    int time = 35;
    int countHold = time;
    int countValue = 32;

    void setColor(Color color);

public:
    RectangleShape shape;
    Text text;
    bool value = false;
    bool active = true;

    Button();
    Button(Vector2f position, Vector2f bounds);
    Button(const Texture& texture, Vector2f position, Vector2f bounds);

    void set(Vector2f position, Vector2f bounds);
    void setTexture(const Texture& texture);
    void setText(const Font& font, const std::string& string);
    bool updateToggle(Vector2f mousePos, Event* event);
    bool updateHold(Vector2f mousePos, Event* event);
    void render(RenderTarget* target);
};

#endif