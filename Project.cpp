#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <time.h>



using namespace std;
#define DELAY_CONST 100000

class player;
GameMechs* myGM = nullptr;
Player* myPlayer = nullptr;
bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    srand((unsigned int) time(NULL));

    // [TODO] Initialize any global variables as required.

    exitFlag = false;

    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.

    myGM = new GameMechs(26,13);
    myPlayer = new Player(myGM);

    objPos playerPos;
    objPosArrayList* player = myPlayer -> getPlayerPosList();
    if  (player && player->getSize() > 0){
        player -> getHeadElement(playerPos);
    }

    myGM -> generateFood(&playerPos, player);  

}

//function that gets user inout 
void GetInput(void)
{
    myGM -> getInput();
}


void RunLogic(void)
{

// updating player's direction and movement
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

//has snake eaten?
    objPos head;
    objPosArrayList* body = myPlayer -> getPlayerPosList();
    if (body && body->getSize() > 0)
    {
        body->getHeadElement(head);
    }

    objPos food;
    myGM -> getPosFood(food);
    if (head.x == food.x && head.y == food.y){

        myGM -> generateFood(&head, body);
        myPlayer -> setHasAteFood(true);
    }
    myGM -> clearInput();
    
}
    
  


void DrawScreen(void)
{
    MacUILib_clearScreen();   //clear the screen 


    objPosArrayList* body = myPlayer->getPlayerPosList();
    objPos food; 
    myGM->getPosFood(food);
    int i, j, m;

//draw game elements on the screen 
    for (i=0; i < myGM->getBoardSizeY(); i++)
    {

        for (j=0; j< myGM->getBoardSizeX(); j++)
        {
            
            bool draw = false;

            //debug

            for (m=0; m< body->getSize(); m++){

                objPos part;
                body->getElement(part, m);

                if (i == part.y && j == part.x){

                    MacUILib_printf("%c", part.symbol);
                    draw = true;
                    break;
                }
            }

            if (draw) continue;

            // draw border walls

            if (i == 0 || j== 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }

            //food

            else if(i == food.y && j == food.x)
            {
                MacUILib_printf("%c", food.symbol);
            
            }
            
            //rest of the board
            else
            {

                MacUILib_printf(" ");
            }
        }

        MacUILib_printf("\n");
    }


    if (myGM -> getLoseFlag() == false)
    {

        MacUILib_printf("Positon of Food: <%d, %d> \n", food.x, food.y);
        MacUILib_printf("Score: %d\n", myPlayer->getScore());
        MacUILib_printf("Press ] to exit the game");

    }

    else if(myGM->getLoseFlag() == true)
    {
        MacUILib_clearScreen();
        MacUILib_printf("\n\nYou Lost!\n");
        MacUILib_printf("Final Game Score: %d\n", myPlayer-> getScore());
        MacUILib_Delay(500000);
        myGM->getExitFlagStatus();

    }



}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

    delete myPlayer;
    delete myGM;

    MacUILib_clearScreen();    
    MacUILib_uninit();
}
