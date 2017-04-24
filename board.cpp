#include "board.h"


Board::Board()
{

}


Board::~Board()
{
    for(std::vector<QRect*>::iterator i = squares.begin(); i != squares.end(); i++)
    {
        delete (*i);
    }

    squares.clear();
    squareStat.clear();
}


//Initiated the board by clearing data and setting new values
void Board::init()
{
    int x = 0;
    int y = 0;
    moves = 0;

    for(std::vector<QRect*>::iterator i = squares.begin(); i != squares.end(); i++)
    {
        delete (*i);
    }

    squares.clear();
    squareStat.clear();

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            x = (PIECE_SIZE+5) * j;
            y = (PIECE_SIZE+5) * i;

            squares.push_back(new QRect(x, y, PIECE_SIZE,PIECE_SIZE));
            squareStat.push_back(0);
        }
    }
}


//Find square pressed, checks if empty, if empty then it fills it
QPoint Board::place_piece(QPoint pos)
{
    int chosenSquare = 0;

    for(int i = 0; i < squares.size(); i++)
    {
        if(squares[i]->contains(pos, false))
        {
            chosenSquare = i;
        }
    }

    if(squareStat[chosenSquare] == EMPTY)
    {
        squareStat[chosenSquare] = PLAYER_ID;
        moves++;
        return squares[chosenSquare]->topLeft();
    }
    return QPoint(1000, 1000);
}


//Places the piece for the AI
QPoint Board::AI_piece(int square)
{
    squareStat[square] = AI_ID;
    moves++;
    return squares[square]->topLeft();
}


//Checks if a player has won or if it is a draw
//Inspired by the verious posts at http://stackoverflow.com/questions/5230621/checking-who-won-tic-tac-toe-more-efficient-c
int Board::check_win()
{
    int id;

    //Checks rows
    for(int i = 0; i < (squareStat.size()); i += 3)
    {
        id = squareStat[i];

        if((id != 0) && (squareStat[i+1] == id) && (squareStat[i+2] == id))
        {
            return id;
        }
    }

    //Checks columns
    for(int i = 0; i < (squareStat.size()); i++)
    {
        id = squareStat[i];

        if((id != 0) && (squareStat[i+3] == id) && (squareStat[i+6] == id))
        {
            return id;
        }
    }

    //Checks diagonals
    id = squareStat[4];
    if((id != 0) && ((squareStat[0] == id && squareStat[8] == id) || (squareStat[2] == id && squareStat[6] == id)))
    {
        return id;
    }

    //If all squares are filled but no player has won it's a draw
    if(moves == 9 && id != 0)
    {
        return -1;
    }

    return 0;
}


//Checks the given vector of the board to see if anyone has won
//Used when AI checks all possible moves
int Board::check_win(std::vector<int> checking)
{
    int id;

    for(int i = 0; i < (checking.size()); i += 3)
    {
        id = checking[i];

        if((id != 0) && (checking[i+1] == id) && (checking[i+2] == id))
        {
            return id;
        }
    }

    for(int i = 0; i < (checking.size()); i++)
    {
        id = checking[i];

        if((id != 0) && (checking[i+3] == id) && (checking[i+6] == id))
        {
            return id;
        }
    }

    id = checking[4];
    if((id != 0) && ((checking[0] == id && checking[8] == id) || (checking[2] == id && checking[6] == id)))
    {
        return id;
    }

    if(moves == 9 && id != 0)
    {
        return -1;
    }

    return 0;
}


std::vector<int> Board::return_vector()
{
    return squareStat;
}
