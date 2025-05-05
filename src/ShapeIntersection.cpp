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
#include "Collidable.hpp"
#include "Polygon.hpp"
#include "VectorUtils.hpp"

CollisionStatus polygonIntersectsPolygon(const Polygon& a, const Polygon& b);

CollisionStatus shapesIntersect(const IShape& a, const IShape& b) {
    const Polygon* polygon_a = dynamic_cast<const Polygon*>(&a);
    const Polygon* polygon_b = dynamic_cast<const Polygon*>(&a);
    if (polygon_a && polygon_b)
    {
        return polygonIntersectsPolygon(*polygon_a, *polygon_b);
    }
    return CollisionStatus::None; // Fallback
}

CollisionStatus polygonIntersectsPolygon(const Polygon& a, const Polygon& b)
{
    const std::vector<sf::Vector2f>& pointsA = a.getPoints();
    const std::vector<sf::Vector2f>& pointsB = b.getPoints();

    size_t countA = pointsA.size();
    size_t countB = pointsB.size();

    // Check edge-to-edge intersection
    for (size_t indexA = 0; indexA < countA; ++indexA)
    {
        Vec2::Segment aSegment = { pointsA[indexA], pointsA[(indexA + 1) % countA] };

        for (size_t indexB = 0; indexB < countB; ++indexB)
        {
            Vec2::Segment bSegment = { pointsB[indexB], pointsB[(indexB + 1) % countB] };

            if (Vec2::doSegmentsIntersect(aSegment, bSegment))
            {
                return CollisionStatus::Touching; // Return when edges just touch
            }
        }
    }

    // Check containment: one polygon completely inside the other
    if (a.contains(pointsB[0])) // b inside a
    {
        return CollisionStatus::Contained;
    }
    if (b.contains(pointsA[0])) // a inside b
    {
        return CollisionStatus::Contained;
    }

    // No collision detected
    return CollisionStatus::None;
}

