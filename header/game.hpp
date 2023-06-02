#pragma once

#include "barrel.hpp"
#include "item.hpp"
#include <vector>
#include <ctime>

class Game {

    std::vector<Item*> items;
    Barrel barrel;
    int frameCount;
    int maxScore;
    int maxLives;
    int score;
    int lives;
    int velocity;
    int width;
    int height;
    
    public:

        Game(int width, int height);

        void fall(Item *item);
        void move(Barrel barrel, int x, int y);
        void addScore();
        void addFruit();
        void addBomb();
        void reduceLife();
        void frame();
        void end();
        
        void setMaxScore(int maxScore);
        void setMaxLives(int maxLives);
        void setScore(int score);
        void setLives(int lives);
        void setVelocity(int vel);
        void setWidth(int width);
        void setHeight(int height);

        int getMaxScore();
        int getMaxLives();
        int getScore();
        int getLives();
        int getVelocity();
        vector<Item*>& getItems();
        Barrel& getBarrel();

        void readMaxScore();
        void writeMaxScore();
};