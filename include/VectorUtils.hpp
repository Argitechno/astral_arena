/// ->
/// * @file VectorUtils.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief Helper functions for our 2d vectors. Inline cause they are small, don't need cpp.
/// * @version 0.1
/// * @date 2025-04-28
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#ifndef VECTOR_UTILS_HPP
#define VECTOR_UTILS_HPP

#include <SFML/System.hpp>
#include <cmath>


namespace Vec2
{

    struct Segment
    {
        sf::Vector2f start;
        sf::Vector2f end;

        Segment(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
            : start(startPoint), end(endPoint) {}
    };

    struct Triangle
    {
        sf::Vector2f a;
        sf::Vector2f b;
        sf::Vector2f c;

        Triangle(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c)
            : a(a), b(b), c(c) {}
    };

    struct Circle
    {
        float x;
        float y;
        float radius;

        Circle(const float& x, const float& y, const float& radius)
            : x(x), y(y), radius(radius) {}
    };

    struct Rectangle
    {
        float x;
        float y;
        float width;
        float height;

        Rectangle(const float& x, const float& y, const float& width, const float& height)
            : x(x), y(y), width(width), height(height) {}
    };

    /// @brief Return the length (magnitude) of v.
    /// @param v 
    /// @return 
    inline float length(const sf::Vector2f& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    /// @brief Return v normalized to length 1 (if non-zero).
    /// @param v 
    /// @return 
    inline sf::Vector2f normalize(const sf::Vector2f& v)
    {
        float len = length(v);
        if (len != 0.f)
        {
            return sf::Vector2f(v.x / len, v.y / len);
        }
        return sf::Vector2f(0.f, 0.f);
    }

    /// @brief Dot-product of a and b.
    /// @param a 
    /// @param b 
    /// @return 
    inline float dot(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    /// @brief Cross-product of a and b (returns a scalar in 2D).
    inline float cross(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return a.x * b.y - a.y * b.x;
    }

    /// @brief Perpendicular (normal) to the right: rotates v by +90°.
    //          Negative reciprical
    /// @param v 
    /// @return 
    inline sf::Vector2f perp(const sf::Vector2f& v)
    {
        return sf::Vector2f(-v.y, v.x);
    }

    /// @brief Get the angle of the given vector
    /// @param A 
    /// @return 
    inline float angleOf(const sf::Vector2f& A) {
        return std::atan2(A.y, A.x);
    }

    /// @brief Reflect a vector off a normal
    /// @param velocity 
    /// @param normal 
    /// @return 
    inline sf::Vector2f reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal)
    {
        return velocity - 2 * dot(velocity, normal) * normal;
    }

    inline float degreesToRadians(float deg)
    {
        return deg/180.f * M_PI;
    }

    inline float radiansToDegrees(float rad)
    {
        return rad/M_PI * 180.f;
    }
    
    bool doSegmentsIntersect(const Segment& a, const Segment& b);
}



#endif
