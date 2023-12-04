#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    score = 0;

    // more actions to be included

    //initial obj pos

    int midX = mainGameMechsRef->getBoardSizeX() / 2;
    int midY = mainGameMechsRef->getBoardSizeY() / 2;
    
    objPos startPos(midX, midY, '?');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(startPos);
    ateFood = false;

}



int Player:: getScore() const 
{
    if (playerPosList != nullptr){

        return playerPosList->getSize() - 1; // -1 to exclude the head
    }
    return 0; //if player pos is empty/null

}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPosList()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    char input = mainGameMechsRef->getInput();
    switch(input)
        {                      
            case ']':  // exit
                mainGameMechsRef -> setExitTrue();
                break;
            case 'w':
                if (myDir != DOWN)
                {
                    myDir = UP;
                }
                break;
            case 's':
                if (myDir != UP)
                {
                    myDir = DOWN;
                }
                break;
            case 'a':
                if (myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;
            case 'd':
                if (myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break; 

            default:
                break; 
        }     

        mainGameMechsRef->clearInput();


}


void Player::movePlayer()
{
    objPos newPos;
    playerPosList->getHeadElement(newPos);


    if (myDir == RIGHT) 
    {
        newPos.x = (newPos.x + 1) % (mainGameMechsRef->getBoardSizeX() -2);  
    }
    else if (myDir == LEFT) 
    {
        newPos.x = (newPos.x - 1) % (mainGameMechsRef->getBoardSizeX() - 2) % (mainGameMechsRef -> getBoardSizeX() -2);  
        
    }
    else if (myDir == DOWN) 
    {
       newPos.y = (newPos.y + 1) % (mainGameMechsRef->getBoardSizeY() - 2);  
    
    }
    else if (myDir == UP) 
    {
        newPos.y = (newPos.y - 1) % (mainGameMechsRef->getBoardSizeY() - 2) % (mainGameMechsRef -> getBoardSizeY() - 2);  
    } 


// if pos of snake goes over border
    if (newPos.x <=0)
    {
        newPos.x += (mainGameMechsRef -> getBoardSizeX() -2);
    }

    if (newPos.y <=0) 
    {
        newPos.y += (mainGameMechsRef -> getBoardSizeY() -2);
    }

    if (selfCollision(newPos))
    {
        mainGameMechsRef -> setLoseFlag ();
        return;
    }

    playerPosList -> insertHead(newPos);
   
    if (!ateFood)
    {
        playerPosList -> removeTail();
    }
    else
    {
        ateFood = false;
    }

}


void Player:: setHasAteFood(bool ate)
{
    ateFood = ate;
}


bool Player::selfCollision(const objPos& newHeadPos) const{
    int i;
    objPos part;

    for (i=1; i<playerPosList->getSize(); ++i)
    {
        playerPosList->getElement(part, i);
        if (part.x == newHeadPos.x && part.y == newHeadPos.y) // if head and part are the same pos, they collided
        {
            return true; //this means there is a collision
        }
    }

    return false; //if there isnt collision
}

