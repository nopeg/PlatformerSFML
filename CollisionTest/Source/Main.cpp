#include "Common.h"
#include "Application.h"

//главная функция программы
int main()
{
    std::cout << "start" << std::endl;

    //создаем приложение и запускаем его
    Application game;
    game.run();

    return 0;
}