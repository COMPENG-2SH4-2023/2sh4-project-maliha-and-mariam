#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{ 
}

GameMechs::GameMechs(int boardX, int boardY): 
boardSizeX(boardX) , boardSizeY(boardY), input(0), exitFlag(false){
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}


bool GameMechs::getLoseFlag()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() != 0){
        input = MacUILib_getChar();
    }
        return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}


// generate food for board
void GameMechs::generateFood(objPos *playerPos, objPosArrayList *snake)
{
    int Xnew, Ynew;
    bool unique = false;
    int i;

     while (!unique) {
        Ynew = rand() % boardSizeY;
        Xnew = rand() % boardSizeX;

        unique = true;

        // Check against the player position
        if (Xnew == playerPos->x && Ynew == playerPos->y) {
            unique = false;
            continue;
        }
        
        // Check against the snake body
        for (i = 0; i < snake->getSize(); ++i) {
            objPos part;
            snake->getElement(part, i);
            if (part.x == Xnew && part.y == Ynew) {
                unique = false;
                break;
            }
        }
        
        if (Xnew == boardSizeX - 1 || Ynew == boardSizeY - 1 || Xnew == 0 || Ynew == 0) {
            unique = false;
        }
        
        // Add more conditions here if necessary, like checking against other game elements
    }

    food.setObjPos(Xnew, Ynew, 'F'); // for food
}

//get posiition of food
void GameMechs::getPosFood(objPos &returnPos)
{
    returnPos = food;
}