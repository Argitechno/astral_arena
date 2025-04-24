#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Map {

    public:
    Map();
    ~Map(){};
    void run();
    bool isDone() {return mIsDone;};
    sf::RenderWindow& getWindow(); // add this

    protected:
    sf::RenderWindow map;
    sf:: RectangleShape border;
    bool mIsDone;

};


class Powerups {

};

#endif