#include "Common.h"
#include "Animation.h"

//конструкторы и деструктор
Animation::Animation() {}
Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) 
{
    set(texture, imageCount, switchTime);
}
Animation::~Animation() {}

//настройка аниматора
void Animation::set(Texture* texture, Vector2u imageCount, float switchTime)
{
    //загружаем файл и делим его на ряды
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

//обновление
void Animation::update(int row, bool reverseDirection, float deltaT) 
{
    //каждый ряд является отдельной анимацией
    //в ряду несколько кадров

    currentImage.y = row;
    totalTime += deltaT;
    this->switchTime = switchTime;

    //сменяем кадры
    if (totalTime >= switchTime) 
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x) 
        {
            currentImage.x = 0;
        }
    }

    //обновляем спрайт, выбирая нужный кадр из тайлсета анимации
    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = (currentImage.x + reverseDirection) * abs(uvRect.width);
    uvRect.width = (reverseDirection ? -1 : +1) * abs(uvRect.width);
}