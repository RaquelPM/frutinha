#pragma once

#include <utility>

#include "item.hpp"

class Barrel : public Item {

    public:

        const static int sizeBarrelX;
        const static int sizeBarrelY;
    
        Barrel();
        Barrel(int x, int y);
        std::pair<int, int> getSize();
        bool checkCollisionItem(Item item);
        bool isOutOfBound(int maxX, int maxY);
};