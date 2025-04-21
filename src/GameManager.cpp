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
    if (obj) {
        if (isDynamic) {
            dynamicObjects.push_back(obj);  // Separate dynamic objects
        } else {
            staticObjects.push_back(obj);   // Separate static objects
        }
    }
}

/// @brief Safely remove a object from the vector, making sure to deallocate it's memory.
/// @param object 
void GameManager::removeObject(GameObject* obj)
{
    if (obj) {
        // Remove from dynamic objects
        std::vector<GameObject*>::iterator it = std::find(dynamicObjects.begin(), dynamicObjects.end(), obj);
        if (it != dynamicObjects.end()) {
            delete *it;  // Deallocate memory
            dynamicObjects.erase(it);  // Remove from the vector
            return;
        }

        // Remove from static objects
        it = std::find(staticObjects.begin(), staticObjects.end(), obj);
        if (it != staticObjects.end()) {    
            staticObjects.erase(it);  // Remove from the vector
        }
    }
}

/// @brief Update the game, deltaTime being time since last tick
/// @param deltaTime
void GameManager::update(float deltaTime)
{
    const std::size_t staticCount = staticObjects.size();
    for (std::size_t idx = 0; idx < staticCount; ++idx) {
        staticObjects[idx]->update(deltaTime);
    }

    const std::size_t dynamicCount = dynamicObjects.size();
    for (std::size_t idx = 0; idx < dynamicCount; ++idx) {
        dynamicObjects[idx]->update(deltaTime);
    }
}

/// @brief Draw all objects to the window.
/// @param window 
void GameManager::draw(sf::RenderWindow& window)
{
    // Draw dynamic objects
    const std::size_t dynamicCount = dynamicObjects.size();
    for (std::size_t idx = 0; idx < dynamicCount; ++idx) {
        // Explicitly check if the object can be drawn by checking if it's a sf::Drawable
        sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(dynamicObjects[idx]);
        if (drawable) {
            window.draw(*drawable);
        }
    }

    // Draw static objects
    const std::size_t staticCount = staticObjects.size();
    for (std::size_t idx = 0; idx < staticCount; ++idx) {
        // Explicitly check if the object can be drawn by checking if it's a sf::Drawable
        sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(staticObjects[idx]);
        if (drawable) {
            window.draw(*drawable);
        }
    }
}