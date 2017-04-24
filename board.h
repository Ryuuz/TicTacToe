#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QRect>
#include "define.h"

class Board
{
    public:
        Board();
        ~Board();
        void init();
        QPoint place_piece(QPoint pos);
        QPoint AI_piece(int square);
        int check_win();
        int check_win(std::vector<int> checking);
        std::vector<int> return_vector();

    private:
        int moves;
        std::vector<QRect *> squares;
        std::vector<int> squareStat;
};

#endif // BOARD_H
