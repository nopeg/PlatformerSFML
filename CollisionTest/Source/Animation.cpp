#include "Common.h"
#include "Animation.h"

Animation::Animation() {}
Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) 
{
    set(texture, imageCount, switchTime);
}

Animation::~Animation() {}

void Animation::set(Texture* texture, Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);

}

void Animation::update(int row, bool reverseDirection, float deltaT) {
    currentImage.y = row;
    totalTime += deltaT;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = (currentImage.x + reverseDirection) * abs(uvRect.width);
    uvRect.width = (reverseDirection ? -1 : +1) * abs(uvRect.width);
}