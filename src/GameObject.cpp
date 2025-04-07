/**
 * @file GameObject.cpp
 * @author Caleb Blondell (crblondell@students.nic.edu)
 * @brief 
 * @version 0.1
 * @date 2025-04-07
 * 
 * 
 */

#include "GameObject.hpp"

GameObject() = default;
virtual ~GameObject() = default;

virtual void update() = 0;  // Pure virtual update method
virtual void draw() = 0;    // Pure virtual draw method