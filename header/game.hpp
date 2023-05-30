#pragma once

#include "barrel.hpp"
#include "item.hpp"
#include <vector>
#include <ctime>

class Game {

    public:
        std::vector<Item> items;
        Barrel barrel;
        int score;
        int maxScore;
        int lives;
        int maxLives;

        void move(Item item);
        void addScore();
        void addItem();
        void reduceLife();
};