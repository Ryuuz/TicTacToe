#include "ai.h"


AI::AI(Board *board)
{
    gameBoard = board;
}


AI::~AI()
{
    delete gameBoard;
}

//Looks for the best move by going through them all and giving them a score based on outcome
//AI is the max player
int AI::minimax(std::vector<int> boardState, bool humanPlayer)
{
        int winner;
        int move = -1;

        //Sets score depending on who's move it is simulating
        int score = ((humanPlayer) ? 100 : -100);

        winner = gameBoard->check_win(boardState);

        switch(winner)
        {
            case -1 : return 0;
            break;

            case 1 : return -10;
            break;

            case 2 : return 10;
            break;
        }

        for(int i = 0; i < boardState.size(); i++)
        {
            if(boardState[i] == 0)
            {
                boardState[i] = ((humanPlayer) ? PLAYER_ID : AI_ID);
                int tempScore = minimax(boardState, !humanPlayer);

                if(humanPlayer && tempScore < score)
                {
                    score = tempScore;
                    move = i;
                }
                else if(!humanPlayer && tempScore > score)
                {
                    score = tempScore;
                    move = i;
                }

                boardState[i] = 0;
            }
        }

        if(move == -1)
        {
            return 0;
        }

        return score;
}


//The AI makes a random move, not caring about what the best move would be
int AI::random_move(std::vector<int> boardState)
{
    int randomSquare;

    do
    {
        randomSquare = rand() % 9;
    }while(boardState[randomSquare] != 0);

    return randomSquare;
}
