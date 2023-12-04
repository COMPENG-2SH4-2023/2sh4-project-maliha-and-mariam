#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.


objPosArrayList:: objPosArrayList(): sizeList(0), sizeArray(200){
    int i;
    aList = new objPos[sizeArray];
    for (i=0; i<sizeArray; i++){
        aList[i] = objPos();
    }
}

objPosArrayList:: ~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList:: getSize()
{
    return sizeList;
}

void objPosArrayList:: insertHead(objPos thisPos)
{
    if (sizeList >= sizeArray){
        resizeArray(sizeArray *2);
    }
    int i;
    for (i = sizeList; i>0; i--)
    {
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    sizeList++;

}


void objPosArrayList:: insertTail(objPos thisPos){

    if (sizeList >= sizeArray) {
    resizeArray(sizeArray * 2); // Double the size
    }
    
    aList[sizeList] = thisPos;
    sizeList++;

}



void objPosArrayList:: removeHead(){

    if (sizeList > 0) {
        int i = 0;
        for (i =0; i < sizeList - 1; i++) {
            aList[i] = aList[i + 1];
        }
        sizeList--;
    }
}



void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos){

    if (sizeList > 0){
        returnPos = aList [0];
    }

}

void objPosArrayList::getTailElement(objPos &returnPos){

    if (sizeList > 0){
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index){

    if (index >= 0 && index < sizeList){

        returnPos = aList[index];
    }
    else{
        returnPos = objPos();
    }

}


void objPosArrayList::resizeArray(int newCapacity) {
    objPos* newList = new objPos[newCapacity];
    
    int i = 0;
    for (i=0; i < sizeList ; i++) {
        newList[i] = aList[i];
    }
    delete[] aList;
    aList = newList;
    sizeArray = newCapacity;
}

