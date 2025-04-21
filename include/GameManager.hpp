/**
 * @file GameManager.hpp
 * @author Caleb Blondell (crblondell@students.nic.edu)
 * @brief 
 * @version 0.1
 * @date 2025-04-07
 * 
 * 
 */

#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

/// @brief Manage the game. It can add and remove objects, load a map, update itself and all the ojbects, and draw all the objects.
class GameManager {
    private:
        std::vector<GameObject*> staticObjects;
        std::vector<GameObject*> dynamicObjects;
    public:
        /// @brief Add an object to the vector of objects.
        /// @param object 
        void addObject(GameObject* obj, bool isDynamic);

        /// @brief Safely remove a object from the vector, making sure to deallocate it's memory.
        /// @param object 
        void removeObject(GameObject* obj);

        /// @brief Load a map from a file.
        /// @param mapPath 
        void loadMap(const std::string& mapPath);

        /// @brief Update the game, deltaTime being time since last tick
        /// @param deltaTime
        void update(float deltaTime);

        /// @brief Draw all objects to the window.
        /// @param window 
        void draw(sf::RenderWindow& window);

        /// @brief Handle all input and move players accordinglly.
        void handleInput();
};


#endif