#include "../header/game.hpp"
#include <fstream>
#include <iostream>

Game::Game(int width, int height){
    frameCount = 0; 
    setWidth(width);
    setHeight(height);
    readMaxScore();
    setMaxLives(3);
    setScore(0);
    setLives(3);
    setVelocity(5);
}

void Game::fall(Item *item){
    item->setY(item->getY() + getVelocity());
}

void Game::move(Barrel barrel, int x, int y){
    barrel.setX(x);
    barrel.setY(y);
}

void Game::addScore(){

    setScore(getScore() + 5);
}

void Game::addFruit(){
    int x = rand() % (width - Item::size);
    int y = 0;
    int type = rand() % 4;

    Item *item = new Item(x, y, type);
    items.push_back(item);
}

void Game::addBomb(){
    int x = rand() % (width - Item::size);
    int y = 0;

    Item *item = new Item(x, y, BOMBA);
    items.push_back(item);
}

void Game::reduceLife(){
    if(getLives() > 1){
        setLives(getLives() - 1);
    }else{
        end();
        throw ("Game Over, your points: " + to_string(getScore()));
    }
}

void Game::frame(){
    frameCount++;
    if(frameCount % (int)(60 * 80/(80 + score)) == 0){
   
        addFruit();
        if(rand() % 10 == 0){
            addBomb();
        }
        frameCount = 0;
    }

    for(size_t i = 0; i < items.size(); i++){

        fall(items[i]);

        if(items[i]->isOutOfBound(height)){

            if(items[i]->getType() != BOMBA){
                try {
                    reduceLife();
                }catch(const char* msg) {
                    throw msg;
                }
            }

            delete items[i];
            items.erase(items.begin() + i);
        } else if(barrel.checkCollisionItem(*items[i])){

            if(items[i]->getType() == BOMBA){
                reduceLife();
            }else{
                addScore();
            }
            delete items[i];
            items.erase(items.begin() + i);
        }
    }
}

void Game::end(){
    if(getScore() > getMaxScore()){
        setMaxScore(getScore());
        writeMaxScore();
    }
}

void Game::setMaxScore(int maxScore){

    this->maxScore = maxScore;
}

void Game::setMaxLives(int maxLives){

    this->maxLives = maxLives;
}

void Game::setScore(int score){

    this->score = score;
}

void Game::setLives(int lives){

    this->lives = lives;
}

void Game::setVelocity(int vel){

    this->velocity = vel;
}

void Game::setWidth(int width){

    this->width = width;
}

void Game::setHeight(int height){

    this->height = height;
}

int Game::getMaxScore(){

    return this->maxScore;
}

int Game::getMaxLives(){

    return this->maxLives;
}

int Game::getScore(){

    return this->score;
}

int Game::getLives(){

    return this->lives;
}

int Game::getVelocity(){

    return this->velocity;
}

vector<Item*>& Game::getItems(){
    
    return items;
}

Barrel& Game::getBarrel(){
    return this->barrel;
}

int Game::getWidth(){

    return this->width;
}

int Game::getHeight(){

    return this->height;
}

void Game::readMaxScore(){

    ifstream file;
    file.open("assets/maxScore.txt");

    if(file.is_open()){
        file >> maxScore;
    }else{
        cout << "Erro ao abrir arquivo" << endl;
    }

    file.close();
}

void Game::writeMaxScore(){

    ofstream file;
    file.open("assets/maxScore.txt");

    if(file.is_open()){
        file << maxScore;
    }else{
        cout << "Erro ao abrir arquivo" << endl;
    }

    file.close();
}

