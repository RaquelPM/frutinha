#include "../header/item.hpp"

Item::Item(){

    setX(0);
    setY(0);
    setType(0);
}

Item::Item(int x, int y, int type, string pathPng){

    setX(x);
    setY(y);
    setType(type);
    setPathPng(pathPng);
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

void Item::setPathPng(string pp){

    this->pathPng = pp;
}

void Item::setType(int type){

    this->type = type;
}

bool Item::isOutOfBound(int maxY){

    return (this->cordY + this->size - 100 > maxY);
}