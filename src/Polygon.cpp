/// ->
/// * @file Polygon.cpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-04-28
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

// Polygon.cpp
#include "Polygon.hpp"
#include "VectorUtils.hpp"
#include <cmath>
#include <cassert>

// ---------- Overloaded Methods ----------

Polygon::Polygon(const std::vector<sf::Vector2f>& points, const sf::Vector2f& position) :
    m_localPoints(points),
    m_transformedPoints(points),
    m_perimeterCached(0.f),
    m_areaCached(0.f),
    m_centroidCached(0.f, 0.f),
    m_boundsCached(sf::FloatRect(0, 0, 0, 0)),
    m_transformCache(sf::Transform::Identity),
    m_valid(true)
{
    setPosition(position);
    assert(!isSelfIntersecting() && "Self-intersecting polygon detected.");
    updateCache(); // Compute everything based on initial points and transform
}


bool Polygon::contains(const sf::Vector2f& point) const
{
    updateCacheIfNeeded();
    int count = 0;
    size_t n = m_transformedPoints.size();

    //If we start from the point and cast a ray to the right
    //That ray will intersect an odd number of edges of the shape
    //If it is in the shape. An even amount of times if not.

    for (size_t idx = 0; idx < n; idx++) {
        const sf::Vector2f& a = m_transformedPoints[idx];
        const sf::Vector2f& b = m_transformedPoints[(idx + 1) % n];
        bool withinYRange = (a.y > point.y) != (b.y > point.y);
        if (!withinYRange) continue;

        // Compute the slope and intersection x-coordinate of the edge at point.y
        float dy = b.y - a.y;
        float dx = b.x - a.x;
        float t = (point.y - a.y) / (dy + 0.0001f); // epsilon to avoid divide-by-zero
        float intersectionX = a.x + t * dx;
        if (point.x < intersectionX)
        {
            count++;
        }
    }

    return count % 2 == 1;
}

float Polygon::getArea() const
{
    updateCacheIfNeeded();
    return m_areaCached;
}

float Polygon::getPerimeter() const
{
    updateCacheIfNeeded();
    return m_perimeterCached;
}

ShapeType Polygon::getType() const
{
    return ShapeType::Polygon;
}

sf::Vector2f Polygon::getCentroid() const
{
    updateCacheIfNeeded();
    return m_centroidCached;
}

sf::FloatRect Polygon::getBounds() const
{
    updateCacheIfNeeded();
    return m_boundsCached;
}

bool Polygon::intersects(const IShape& other) const
{
    if (!getBounds().intersects(other.getBounds()))
    {
        return false;
    }
    return shapesIntersect(*this, other);
}

// ---------- Cache Logic ----------

void Polygon::updateCacheIfNeeded() const
{
    if (m_valid || m_transformCache != getTransform())
    {
        updateCache();
    }
}

void Polygon::updateCache() const
{
    const sf::Transform& t = getTransform();
    m_transformCache = t;
    m_valid = false;
    size_t count = m_localPoints.size();

    m_transformedPoints.clear();
    m_transformedPoints.reserve(m_localPoints.size());

    for (size_t idx = 0; idx < count; idx++) {
        sf::Vector2f pt = m_localPoints[idx];
        m_transformedPoints.push_back(t.transformPoint(pt));
    }

    // Recalculate perimeter
    m_perimeterCached = 0.f;
    count = m_transformedPoints.size();
    for (size_t idx = 0; idx < count; idx++) {
        const sf::Vector2f& a = m_transformedPoints[idx];
        const sf::Vector2f& b = m_transformedPoints[(idx + 1) % count];
        m_perimeterCached += Vec2::length(b - a);
    }

    // Recalculate area using shoelace formula
    //  Future: Don't have to do the whole calculation for area, it only changes with scale
    //  and at that, it is just the area before transformation, * xscale * yscale
    m_areaCached = 0.f;
    for (size_t idx = 0; idx < count; idx++) {
        const sf::Vector2f& a = m_transformedPoints[idx];
        const sf::Vector2f& b = m_transformedPoints[(idx + 1) % count];
        m_areaCached += Vec2::cross(a, b);
    }
    m_areaCached = std::abs(m_areaCached) * 0.5f;

    // Recalculate centroid
    float cx = 0.f, cy = 0.f;
    for (size_t idx = 0; idx < count; idx++) {
        const sf::Vector2f& a = m_transformedPoints[idx];
        const sf::Vector2f& b = m_transformedPoints[(idx + 1) % count];
        float cross = Vec2::cross(a, b);
        cx += (a.x + b.x) * cross;
        cy += (a.y + b.y) * cross;
    }
    float factor = m_areaCached ? 1.0f / (6.0f * m_areaCached) : 0.f;
    m_centroidCached = { std::abs(cx * factor), std::abs(cy * factor) };

    // Recalculate bounds
    float minX = std::numeric_limits<float>::infinity();
    float maxX = -minX;
    float minY = minX;
    float maxY = -minY;

    for (size_t idx = 0; idx < count; idx++)
    {
        sf::Vector2f pt = m_transformedPoints[idx];
        minX = std::min(minX, pt.x);
        maxX = std::max(maxX, pt.x);
        minY = std::min(minY, pt.y);
        maxY = std::max(maxY, pt.y);
    }

    m_boundsCached = sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
}

bool Polygon::isSelfIntersecting() const
{
    size_t pointCount = m_localPoints.size();
    //Go over each pair of edges and test for intersection.
    for (size_t idx = 0; idx < pointCount; ++idx)
    {
        Vec2::Segment a = {m_localPoints[idx], m_localPoints[(idx + 1) % pointCount]};

        for (size_t jdx = idx + 1; jdx < pointCount; jdx++)
        {
            // Skip adjacent edges (they share a point, which is not a true intersection)
            if 
            (
                (jdx == (idx + 1) % pointCount) ||
                ((idx == 0) && (jdx == pointCount - 1))
            )
            {
                continue;
            }
            
            Vec2::Segment b = {m_localPoints[jdx], m_localPoints[(jdx + 1) % pointCount]};

            if (Vec2::doSegmentsIntersect(a, b))
            {
                return true;
            }
        }
    }

    return false;
}

// ---------- Public Methods (i get/set) ----------

const std::vector<sf::Vector2f>& Polygon::getPoints() const
{
    updateCacheIfNeeded();
    return m_transformedPoints;
}

void Polygon::setPoints(const std::vector<sf::Vector2f>& localPoints)
{
    m_localPoints = localPoints;
    updateCache();
}
