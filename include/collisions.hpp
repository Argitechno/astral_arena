/// ->
/// * @brief 
/// * 
/// * @param triangle 
/// * @param rect 
/// * @return true 
/// * @return false 
/// <-

#if !defined(COLLISIONS_HPP)
#define COLLISIONS_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "VectorUtils.hpp"

bool checkTriangleCollision(const Vec2::Triangle& triA, const Vec2::Triangle& triB);

bool checkCircleCollision(const Vec2::Circle& circleA, const Vec2::Circle& circleB);

bool checkRectangleCollision(const Vec2::Rectangle& rectA, const Vec2::Rectangle& rectB);

bool checkTriangleRectangleCollision(const Vec2::Triangle& tri, const Vec2::Rectangle& rect);

bool checkTriangleCircleCollision(const Vec2::Triangle& tri, const Vec2::Circle& circle);

#endif // COLLISIONS_HPP

