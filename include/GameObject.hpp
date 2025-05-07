/**
 * @file GameObject.hpp
 * @author Caleb Blondell (crblondell@students.nic.edu)
 * @brief 
 * @version 0.1
 * @date 2025-04-07
 * 
 * 
 */

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

/// @brief The primary responsiblity of a GameObject is to update itself. 
/// @note      It may or may not be drawable (a timer is not drawable).
/// @note      It may or may not be collideable  (a title for the game would be drawable but not collidable)
/// @note      But no matter what, it needs to update.
class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject() = default;
    
        virtual void update(float deltaTime) = 0;  // Pure virtual update method
};

#endif