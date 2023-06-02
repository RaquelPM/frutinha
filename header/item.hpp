#pragma once
#include <string>
#include <vector>

using namespace std;

enum{LARANJA,MELANCIA,MORANGO,KIWI,BOMBA, BARRIL};

class Item{
    
    protected:
        int type;
        int cordX;
        int cordY;

        string pathPng;

    public:
        const static int size = 82; //size in pixels of the square png that represents the item
        Item();
        Item(int x, int y, int type);
        int getX();
        int getY();
        int getSize();
        int getType();
        string getPNG();
        void setPathPng();
        void setX(int x);
        void setY(int y);
        void setType(int type);
        bool isOutOfBound(int maxY);
};