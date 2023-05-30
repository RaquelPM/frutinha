#pragma once
#include <string>

using namespace std;

enum{LARANJA,MELANCIA,MORANGO,KIWI,BOMBA,BARRIL};

class Item{

    const static int size = 82; //size in pixels of the square png that represents the item
    
    protected:
        int type;
        int cordX;
        int cordY;

        string pathPng;

    public:
        Item();
        Item(int x, int y, int type, string pathPng);
        int getX();
        int getY();
        int getSize();
        int getType();
        string getPNG();
        void setPathPng(string pp);
        void setX(int x);
        void setY(int y);
        void setType(int type);
        bool isOutOfBound(int maxY);
};