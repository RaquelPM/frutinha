#include "../header/item.hpp"

Item::Item(){

    setX(0);
    setY(0);
    setType(0);
}

Item::Item(int x, int y, int type){

    setX(y);
    setY(x);
    setType(type);
}

int Item::getX(){

    return this->cordX;
}

int Item::getY(){

    return this->cordY;
}

int Item::getType(){

    return this->type;
}

void Item::setX(int x){

    this->cordX = x;
}

void Item::setY(int y){

    this->cordY = y;
}

void Item::setType(int type){

    this->type = type;
}