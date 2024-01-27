#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

//класс анимации
class Animation 
{
private:
    //переменные
    Vector2u imageCount;
    Vector2u currentImage;
    float totalTime;

public:
    //скорость обновления кадров
    float switchTime;
    //прямоугольник текстуры
    IntRect uvRect;

    //конструкторы и деструктор
    Animation();
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    ~Animation();
    //функции
    void set(Texture* texture, Vector2u imageCount, float switchTime);
    void update(int row, bool reverseDirection, float deltaT);
};

#endif