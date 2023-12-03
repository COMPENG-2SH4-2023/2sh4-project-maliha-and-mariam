#include "objPos.h"



// class code for the obj position and symbol


objPos::objPos()   //default contructor
{
    x = 0;
    y = 0;
    symbol = 0; //NULL
}

objPos::objPos(objPos &o) //copy consturctor creates new object by copying 
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}


objPos::objPos(int xPos, int yPos, char sym) //initializes specific values
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::setObjPos(objPos o)  //set obj to x and y
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym) //of passing values
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::getObjPos(objPos &returnPos) //sets one value to another for the current object
{
    returnPos.setObjPos(x, y, symbol);
}

char objPos::getSymbol() //returns symbol of object
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) //checks if cureent obj pos is equal to refenced one
{
    return (refPos->x == x && refPos->y == y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) //returns pos if they are equal 
{
    if(isPosEqual(refPos))
        return getSymbol();
    else
        return 0;
}
