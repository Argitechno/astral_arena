/// ->
/// * @file VectorUtils.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-05-04
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#include "VectorUtils.hpp"

bool Vec2::doSegmentsIntersect(const Segment& a, const Segment& b)
    {
        sf::Vector2f dirA = a.end - a.start;
        sf::Vector2f dirB = b.end - b.start;
        sf::Vector2f offset = b.start - a.start;

        float denominator = cross(dirA, dirB);

        // If denominator is zero, segments are parallel or colinear
        if (denominator == 0.0f)
            return cross(offset, dirA) == 0.0f;
       

        // - aFraction is how far along segment A (from a.start to a.end) the intersection point lies.
        float aFraction = cross(offset, dirB) / denominator;
        // - bFraction is how far along segment B (from b.start to b.end) the same intersection point lies.
        float bFraction = cross(offset, dirA) / denominator;

         // If both values are between 0 and 1 inclusive, the segments intersect within their finite lengths.
        return (aFraction >= 0.0f && aFraction <= 1.0f) &&
            (bFraction >= 0.0f && bFraction <= 1.0f);
    }