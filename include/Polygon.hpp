/// ->
/// * @file Polygon.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief We define a polgon here. A type of shape that consists of a number of vertices, connected in a loop.
/// * @version 0.1
/// * @date 2025-04-28
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "Shape.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <cmath>

/// @brief A general polygon shape that implements IShape.
class Polygon : public IShape {
public:
    /// @brief Construct a polygon from world-space vertices. These are shifted to local-space.
    explicit Polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position);

    /// @brief Default destructor
    ~Polygon() override = default;

    /// @brief Does this polygon contain a given point (in world coordinates)
    /// @param point 
    /// @return 
    bool contains(const sf::Vector2f& point) const override;

    /// @brief What is the area if this polygon? 
    /// @return Area using polygon shoelace formula.
    float area() const override;

    /// @brief What is the length of this shapes boundary?
    /// @return Perimeter by summing distance between each point.
    float perimeter() const override;

    /// @brief What is the type of this shape?
    /// @return The shape type.
    ShapeType type() const override { return ShapeType::Polygon; }

    /// @brief What is the geometric center point of this shape?
    /// @return Centroid using polygon centroid formula.
    sf::Vector2f centroid() const override;

    /// @brief What is the smallest rectangle in which this shape can fit?
    /// @return Axis-aligned bounding box.
    sf::FloatRect bounds() const override;

    /// @brief Does this shape intersect another shape?
    /// @param other 
    /// @return True if this shape intersects the other.
    bool intersects(const IShape& other) const override;

    /// @brief Get points in local space
    const std::vector<sf::Vector2f>& getPoints() const;

    /// @brief Get points in global space
    std::vector<sf::Vector2f> getWorldPoints() const;

    /// @brief Set points in global space
    /// @param points 
    void setPoints(const std::vector<sf::Vector2f>& points);

    private:
        /// @brief Local-space polygon vertices
        std::vector<sf::Vector2f>   m_points;

        /// @brief AABB in local space without any transformations applied
        sf::FloatRect               m_localBounds;

        /// @brief AABB in world space before converting to local
        sf::FloatRect               m_worldBounds;
        
        /// @brief Last used transform, if this changes we need to recalc the bounds.
        sf::Transform               m_cachedTransform;
};

#endif // POLYGON_HPP
