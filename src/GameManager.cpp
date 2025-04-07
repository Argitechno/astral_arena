/**
 * @file GameManager.cpp
 * @author Caleb Blondell (crblondell@students.nic.edu)
 * @brief 
 * @version 0.1
 * @date 2025-04-07
 * 
 * 
 */

#include "GameManager.hpp"

/// @brief Add an object to the vector of objects.
/// @param object 
void GameManager::addObject(GameObject* obj, bool isDynamic)
{
    
}

/// @brief Safely remove a object from the vector, making sure to deallocate it's memory.
/// @param object 
void GameManager::removeObject(GameObject* obj)
{
    
}

/// @brief Update the game, deltaTime being time since last tick
/// @param deltaTime
void GameManager::update(float deltaTime)
{
    const std::size_t count = objects.size();
    for (int idx = 0; idx < count; idx++)
    {
        objects[idx]->update(deltaTime);
    }
    
}

/// @brief Draw all objects to the window.
/// @param window 
void GameManager::draw(sf::RenderWindow& window)
{
    const std::size_t count = objects.size();
    for (std::size_t idx = 0; idx < count; ++idx) {
        // Explicitly check if the object can be drawn by checking if it's a sf::Drawable
        sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(objects[idx]);
        if (drawable) {
            window.draw(*drawable);
        }
    }
}