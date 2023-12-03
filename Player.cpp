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

    playerPoslist = new objPosArrayList();
    playerPosList -> insertHead(startPos);
    hasAteFood = false;

}





PLayer:: getScore() const 
{
    if (playerPosList!= nullptr){

        return playerPos->getSize() - 1; // -1 to exclude the head
    }
    return 0; //if player pos is empty/null

}

Player::~Player()
{
    // delete any heap members here
    delete playerPoslist;
}

objArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPoslist;
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    char input = mainGameMechsRef->getInput();
        switch(input)
        {                      
            case ']':  // exit
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
                if (myFSMMode != DOWN)
                {
                    myFSMMode = UP;
                }
                break;
            case 's':
                if (myFSMMode != UP)
                {
                    myFSMMode = DOWN;
                }
                break;
            case 'a':
                if (myFSMMode != RIGHT)
                {
                    myFSMMode = LEFT;
                }
                break;
            case 'd':
                if (myFSMMode != LEFT)
                {
                    myFSMMode = RIGHT;
                }
                break;  
        }     

        mainGameMechsRef->clearInput();


}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos newPos;


    if (myFSMMode == RIGHT) {
        
        
        newPos.x = (newPos.x + 1);  // Wrap around when reaching the boundary
        if (newPos.x > ColSize - 2){
            newPos.x = 1;
        }
    }
    if (myFSMMode == LEFT) {
        newPos.x = (newPos.x - 1);  // Wrap around when reaching the boundary
        if (newPos.x < 1){
            newPos.x = ColSize - 2;
        }
    }
    if (myFSMMode == DOWN) {
        newPos.y = (newPos.y + 1);  // Wrap around when reaching the boundary
        if (newPos.y > RowSize - 2)
            newPos.y = 1;
    }
    if (myFSMMode == UP) {
        newPos.y = (newPos.y - 1);  // Wrap around when reaching the boundary
        if (newPos.y < 1){
            newPos.y = RowSize - 2;
    }
    }  


}



void Player:: setHasAteFood(bool ate)
{
    hasAteFood = ate;
}


bool Player:: selfCollision(const objPos& newHeadPos) const{
    int i;
    objPos part;
    for (i=0; i<playerPosList->getSize(); ++i)
    {
        playerPosList->getElement(part, i);

        if (part.x == newHeadPos.x && part.y == newHeadPos.y) // if head and part are the same pos, they collided
        
        {
            return true; //this means there is a collision
        }
    }

    return false; //if there isnt collision
}

