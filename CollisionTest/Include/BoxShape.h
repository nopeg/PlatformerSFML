#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include <SFML/Graphics.hpp>
using namespace sf;

class BoxShape : public Drawable, public Transformable
{
public:

    BoxShape() = default;
    BoxShape(Vector2f size)
    {
        vertices.resize(4);
        setSize(size);
    }

    FloatRect getGlobalBounds()
    {
        float height = vertices[3].position.y - vertices[0].position.y;
        float left = vertices[0].position.x;
        float top = vertices[0].position.y;
        float width = vertices[1].position.x - vertices[0].position.x;
        FloatRect fr(height, left, top, width);
        return fr;
    }

    void setSize(const Vector2f& size)
    {
        vertices[0].position = Vector2f(0, 0);
        vertices[1].position = Vector2f(0, size.y);
        vertices[2].position = Vector2f(size.x, size.y);
        vertices[3].position = Vector2f(size.x, 0);
    }
    void setColor(const Color& color)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            vertices[i].color = color;
        }
    }

private:

    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(vertices.data(), vertices.size(), Quads, states);
    }

    std::vector<Vertex> vertices;
    Texture texture;
};

#endif