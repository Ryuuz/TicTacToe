#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QImage>
#include <QBrush>
#include <QMouseEvent>
#include <QPoint>

#include "define.h"
#include "button.h"
#include "board.h"
#include "ai.h"

//The game class handles the graphical output, user input, and gameflow
class Game : public QGraphicsView
{
    Q_OBJECT

    public:
        Game();
        ~Game();
        void mousePressEvent(QMouseEvent *event);
        void change_background(QImage *image);
        void player_move(QPoint pos);
        void ai_move();
        void show_start_menu();
        void game_finished(int winner);

    public slots:
        void begin_game();

    private:
        QGraphicsScene *scene;

        QPixmap *xPiece;
        QPixmap *oPiece;
        QPixmap *play;
        QPixmap *replay;

        QImage *startScreen;
        QImage *endScreen;
        QImage *board;

        Board *gameBoard;
        AI *computer;

        bool won;
        bool playersTurn;
};

#endif // GAME_H
