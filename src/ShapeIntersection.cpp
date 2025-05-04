/// ->
/// * @file ShapeIntersection.cpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-05-02
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#include "IShape.hpp"
#include "Polygon.hpp"
#include "VectorUtils.hpp"

bool polygonIntersectsPolygon(const Polygon& a, const Polygon& b);

bool shapesIntersect(const IShape& a, const IShape& b) {
    ShapeType typeA = a.getType();
    ShapeType typeB = b.getType();

    if (typeA == ShapeType::Polygon && typeB == ShapeType::Polygon) {
        return polygonIntersectsPolygon(static_cast<const Polygon&>(a), static_cast<const Polygon&>(b));
    }

    return false; // Fallback
}

bool polygonIntersectsPolygon(const Polygon& a, const Polygon& b)
{
    const std::vector<sf::Vector2f>& pointsA = a.getPoints();
    const std::vector<sf::Vector2f>& pointsB = b.getPoints();

    size_t countA = pointsA.size();
    size_t countB = pointsB.size();

    // Check edge-edge intersection
    for (size_t indexA = 0; indexA < countA; ++indexA)
    {
        Vec2::Segment a = {pointsA[indexA], pointsA[(indexA + 1) % countA]};

        for (size_t indexB = 0; indexB < countB; ++indexB)
        {
            Vec2::Segment b = {pointsB[indexB], pointsB[(indexB + 1) % countB]};

            if (Vec2::doSegmentsIntersect(a, b))
            {
                return true;
            }
        }
    }

    // If no edges intersect, check if one polygon is contained inside the other
    if (a.contains(pointsB[0]) || b.contains(pointsA[0]))
    {
        return true;
    }

    return false; 
}

