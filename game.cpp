#include "game.h"


Game::Game()
{
    won = true;
    gameBoard = new Board();
    computer = new AI(gameBoard);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCREEN_SIZE, SCREEN_SIZE);

    //Loads textures
    xPiece = new QPixmap(":/Images/tic_tac_toe/x_piece.png");
    oPiece = new QPixmap(":/Images/tic_tac_toe/o_piece.png");

    play = new QPixmap(":/Images/tic_tac_toe/start_button.png");
    replay = new QPixmap(":/Images/tic_tac_toe/replay_button.png");

    startScreen = new QImage(":/Images/tic_tac_toe/start_image.png");
    board = new QImage(":/Images/tic_tac_toe/board.png");
    endScreen = new QImage(":/Images/tic_tac_toe/end_screen.png");


    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_SIZE, SCREEN_SIZE);
    setWindowTitle("Tic Tac Toe");

    show();
}


Game::~Game()
{
    scene->clear();
    delete scene;
    delete gameBoard;
    delete computer;

    delete xPiece;
    delete oPiece;
    delete play;
    delete replay;
    delete startScreen;
    delete board;
    delete endScreen;
}


void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(!won)
        {
            if(playersTurn)
            {
                player_move(event->pos());
            }
        }
        else
        {
            QGraphicsView::mousePressEvent(event);
        }
    }
}


void Game::change_background(QImage *image)
{
    scene->clear();
    setBackgroundBrush(QBrush(QImage(*image)));
}


//Lets the player place a piece in chosen square if it is empty
void Game::player_move(QPoint pos)
{
    QPoint tempPoint;
    tempPoint = gameBoard->place_piece(pos);

    //Adds the piece's image to board if it was added sucessfully and checks the state of the game
    if(tempPoint.x() < 1000)
    {
        QPixmap *tempPixmap;
        tempPixmap = xPiece;
        QGraphicsPixmapItem *tempImage = scene->addPixmap(*tempPixmap);
        tempImage->setPos(tempPoint);
        playersTurn = false;

        int win = gameBoard->check_win();

        //The AI makes a move if the game isn't over by a win or draw
        if(win == 0)
        {
            ai_move();
        }
        else
        {
            game_finished(win);
        }
    }
}


//Takes care of the AI's move
void Game::ai_move()
{
    QPoint tempPoint;
    std::vector<int> tempVec = gameBoard->return_vector();
    int move = -1;
    int randomNum = rand() % 100;

    //Determines if the AI should make a random move
    if(randomNum >= 0 && randomNum < RANDOM_CHANCE)
    {
        move = computer->random_move(tempVec);
    }
    else
    {
        int score = -100;

        //Checks all possible moves and chooses the best one
        for(int i = 0; i < tempVec.size(); i++)
        {
            if(tempVec[i] == 0)
            {
                tempVec[i] = AI_ID;
                int tempScore = computer->minimax(tempVec, !playersTurn);
                tempVec[i] = 0;

                if(tempScore > score)
                {
                    score = tempScore;
                    move = i;
                }
            }
        }
    }

    //Makes chosen move and checks the state of the game
    tempPoint = gameBoard->AI_piece(move);

    QPixmap *tempPixmap;
    tempPixmap = oPiece;
    QGraphicsPixmapItem *tempImage = scene->addPixmap(*tempPixmap);
    tempImage->setPos(tempPoint);

    int win = gameBoard->check_win();

    if(win == 0)
    {
        playersTurn = true;
    }
    else
    {
        game_finished(win);
    }
}


//Shows the welcome screen with a button to start the game
void Game::show_start_menu()
{
    change_background(startScreen);

    //Creates the button
    Button *startButton = new Button(play);
    startButton->setPos(((SCREEN_SIZE/2) - (BUTTON_WIDTH/2)), ((SCREEN_SIZE - BUTTON_HEIGHT) - 20));
    connect(startButton, SIGNAL(clicked()), this, SLOT(begin_game()));
    scene->addItem(startButton);

}


//Changes image when game is over, display result, and gives the option for a rematch
void Game::game_finished(int winner)
{
    QGraphicsTextItem *result;

    change_background(endScreen);
    won = true;

    switch(winner)
    {
        case -1 : result = new QGraphicsTextItem(QString("It's a draw"));
        break;

        case 0 : result = new QGraphicsTextItem(QString("This shouldn't happen"));
        break;

        case 1 : result = new QGraphicsTextItem(QString("You won"));
        break;

        case 2 : result = new QGraphicsTextItem(QString("You lose"));
        break;
    }

    QFont textFont("Arial", 50);
    result->setFont(textFont);
    result->setDefaultTextColor(Qt::blue);
    result->setPos(((SCREEN_SIZE/2) - (result->boundingRect().width()/2)), 50);
    scene->addItem(result);

    Button *replayButton = new Button(replay);
    replayButton->setPos(((SCREEN_SIZE/2) - (BUTTON_WIDTH/2)), ((SCREEN_SIZE/2) - (BUTTON_HEIGHT/2)));
    connect(replayButton, SIGNAL(clicked()), this, SLOT(begin_game()));
    scene->addItem(replayButton);
}


//Starts the game by initialising and showing the empty board.
void Game::begin_game()
{
    change_background(board);

    won = false;
    playersTurn = true;
    gameBoard->init();
}
