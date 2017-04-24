#include <QApplication>
#include <ctime>
#include "game.h"

//A tic tac toe game created by Camilla Merete Odegaard using Qt
//Some of the code is based on the tutorials made by Abdullah Aghazadah
//https://www.youtube.com/playlist?list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy

//The code for the AI was inspired by Code made by user MatthewSteel
//https://gist.github.com/MatthewSteel/3158579

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(nullptr));
    Game *game;

    game = new Game();
    game->show();
    game->show_start_menu();

    return a.exec();
}
