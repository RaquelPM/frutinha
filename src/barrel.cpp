#include "../header/barrel.hpp"
#include <iostream>

const int Barrel::sizeBarrelX = 163;
const int Barrel::sizeBarrelY = 82;

Barrel::Barrel() : Item(){

    setType(BARRIL);
}

Barrel::Barrel(int x, int y) : Item(x, y, BARRIL){}

std::pair<int, int> Barrel::getSize(){

    return std::make_pair(Barrel::sizeBarrelX, Barrel::sizeBarrelY);
}

bool Barrel::isOutOfBound(int maxX, int maxY){

    int barrelX = this->getX();
    int barrelY = this->getY();

    return (barrelX < 0 or barrelX + Barrel::sizeBarrelX > maxX or barrelY + Barrel::sizeBarrelY > maxY or barrelY < 0);
}

bool Barrel::checkCollisionItem(Item item){

    int itemX = item.getX();
    int itemY = item.getY();
    int itemSize = item.getSize();

    int barrelX = this->getX();
    int barrelY = this->getY();

    bool isInRangeLeft, isInRangeRight, isInBetween, isInRangeUp;
    //checks if item is in range of barrel, execpt if part of the item is bellow the barrel

    isInRangeLeft = (barrelX >= itemX and barrelX <= itemX + itemSize);
    isInRangeRight = (barrelX + Barrel::sizeBarrelX >= itemX and barrelX + Barrel::sizeBarrelX <= itemX + itemSize);
    isInBetween = (barrelX <= itemX and barrelX + Barrel::sizeBarrelX >= itemX + itemSize);
    isInRangeUp = (barrelY >= itemY and barrelY <= itemY + itemSize);

    if(isInRangeLeft){
        cout << "left" << endl;
    }
    if(isInRangeRight){
        cout << "right" << endl;
    }
    if(isInRangeUp){
        cout << "up" << endl;
    }

    return ((isInRangeLeft or isInRangeRight or isInBetween) and isInRangeUp);
}
