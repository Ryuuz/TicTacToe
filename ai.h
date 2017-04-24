#ifndef AI_H
#define AI_H

#include <cstdlib>
#include "board.h"

class AI
{
    public:
        AI(Board *board);
        ~AI();
        int minimax(std::vector<int> boardState, bool humanPlayer);
        int random_move(std::vector<int> boardState);

    private:
        Board *gameBoard;
};

#endif // AI_H
