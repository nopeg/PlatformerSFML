#ifndef SHAPES_H
#define SHAPES_H

static Color colorOn = Color(255, 0, 0, 255);
static Color colorOff = Color(255, 255, 255, 255);
static Color colorEnterOff = Color(200, 200, 200, 255);
static Color colorEnterOn = Color(200, 0, 0, 255);
static Color colorDisabled = Color(100, 100, 100, 255);

//rectangles
inline RectangleShape newLine(Vector2f pos1, Vector2f pos2, 
    float width, float outlineWidth, Color colorFill, Color outlineColor)
{
    RectangleShape line({ 1, 1 });

    line.setSize({ distance(pos1, pos2), width });
    line.setFillColor(colorFill);
    line.setPosition(pos1);
    line.setRotation(angle(pos2, pos1) * 180.0 / float(PI));
    line.setOutlineThickness(outlineWidth);
    line.setOutlineColor(outlineColor);

    return line;
}

inline RectangleShape newBox(Vector2f bounds, Vector2f pos, 
    float outlineWidth, Color colorFill, Color outlineColor)
{
    RectangleShape box(bounds);
    box.setOrigin({ bounds.x / 2, bounds.y / 2 });
    box.setPosition({ pos.x, pos.y });
    box.setFillColor(colorFill);
    box.setOutlineThickness(outlineWidth);
    box.setOutlineColor(outlineColor);
    return box;
}

//text
inline Text newText(Vector2f pos, const Font& font, const std::string& string, 
    unsigned int chsize, float outlineWidth, Color txtColor, Color outlineColor)
{
    Text txt;

    txt.setFont(font);
    txt.setString(string);
    txt.setCharacterSize(chsize);
    txt.setFillColor(txtColor);
    txt.setOutlineColor(outlineColor);
    txt.setOutlineThickness(outlineWidth);
    FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(pos);

    return txt;
}

//sprite
inline Sprite newSprite(Texture& texture, Vector2f pos, 
    Vector2f scale, Vector2f origin, Color colorSprite)
{
    Sprite sprite;

    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(scale);
    sprite.setColor(colorSprite);
    sprite.setOrigin(origin);

    return sprite;
}

#endif