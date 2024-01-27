#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

//����� ��������
class Animation 
{
private:
    //����������
    Vector2u imageCount;
    Vector2u currentImage;
    float totalTime;

public:
    //�������� ���������� ������
    float switchTime;
    //������������� ��������
    IntRect uvRect;

    //������������ � ����������
    Animation();
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    ~Animation();
    //�������
    void set(Texture* texture, Vector2u imageCount, float switchTime);
    void update(int row, bool reverseDirection, float deltaT);
};

#endif