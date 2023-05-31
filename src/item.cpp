#include "../header/item.hpp"


string paths[] = {"assets/orange.png",
    "assets/watermelon.png",
    "assets/strawberry.png",
    "assets/kiwi.png",
    "assets/bomb.png",
    "assets/cesta.png"};

Item::Item(){

    setX(0);
    setY(0);
    setType(0);
}

Item::Item(int x, int y, int type){

    setX(x);
    setY(y);
    setType(type);
    setPathPng();
}

string Item::getPNG(){

    return this->pathPng;
}

int Item::getX(){

    return this->cordX;
}

int Item::getY(){

    return this->cordY;
}

int Item::getSize(){

    return this->size;
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

void Item::setPathPng(){

    this->pathPng = paths[type];
}

void Item::setType(int type){

    this->type = type;
}

bool Item::isOutOfBound(int maxY){

    return (this->cordY + this->size >= maxY);
}