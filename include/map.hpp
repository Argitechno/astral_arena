#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "ObjectManager.hpp"
#include <array>
#include "asteroid.hpp"
#include "block.hpp"
#include "Spaceship.hpp"

class Map : public ObjectManager {

    public:
        Map();
        ~Map(){};

        /// ->
        /// * @brief Override the update method from GameObject
        /// * 
        /// * @param deltaTime 
        /// <-
        void update(float deltaTime) override;

        /// @brief Draw all objects to the window.
        /// @param window 
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void userInput();

        /// @brief Reset the map.
        void reset();

    protected:
        sf::RenderWindow map;
        sf:: RectangleShape border;

    private:
        sf::Texture m_sharedTexture;
        std::array<Asteroid, 4> m_Asteroids;
        std::array<Block, 8> m_Blocks;
        std::array<Spaceship, 2> m_Players;

};
#endif