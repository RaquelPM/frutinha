#pragma once

enum{LARANJA,MELANCIA,MORANGO,KIWI,BOMBA,BARRIL};

class Item{

    const static int size = 164; //size in pixels of the square png that represents the item
    
    protected:
        int type;
        int cordX;
        int cordY;

    public:
        Item();
        Item(int x, int y, int type);
        int getX();
        int getY();
        int getSize();
        int getType();
        void setX(int x);
        void setY(int y);
        void setType(int type);
        bool isOutOfBound(int maxY);
};