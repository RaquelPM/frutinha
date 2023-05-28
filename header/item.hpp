#pragma once

class Item{

    int cordX;
    int cordY;
    int type;

    public:
        Item();
        Item(int x, int y, int type);
        int getX();
        int getY();
        int getType();
        void setX(int x);
        void setY(int y);
        void setType(int type);
        void checkColision(int x, int y);
};