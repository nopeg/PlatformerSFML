#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation 
{
public:
    Animation();
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    ~Animation();
    void set(Texture* texture, Vector2u imageCount, float switchTime);
    void update(int row, bool reverseDirection, float deltaT);

    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

};

#endif