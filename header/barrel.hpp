#pragma once

#include <utility>

#include "item.hpp"

class Barrel : public Item {

    const static int sizeBarrelX = 180;
    const static int sizeBarrelY = 180;
    
    public:

        Barrel();
        Barrel(int x, int y);
        std::pair<int, int> getSize();
        bool checkCollisionItem(Item item);
        bool isOutOfBound(int maxX, int maxY);
};