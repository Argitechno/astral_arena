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

#include "IShape.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>


/// @brief A general polygon shape that implements IShape.
class Polygon : public IShape
{
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
        float getArea() const override;

        /// @brief What is the length of this shapes boundary?
        /// @return Perimeter by summing distance between each point.
        float getPerimeter() const override;

        /// @brief What is the type of this shape?
        /// @return The shape type.
        ShapeType getType() const override;

        /// @brief What is the geometric center point of this shape?
        /// @return Centroid using polygon centroid formula.
        sf::Vector2f getCentroid() const override;

        /// @brief What is the smallest rectangle in which this shape can fit? Has to recalculate the bounds if the transform changed.
        /// @return Axis-aligned bounding box.
        sf::FloatRect getBounds() const override;

        /// @brief Does this shape intersect another shape?
        /// @param other 
        /// @return True if this shape intersects the other.
        bool intersects(const IShape& other) const override;

        /// @brief Access the transformed polygon points.
        const std::vector<sf::Vector2f>& getPoints() const;

        /// @brief Access the transformed polygon points.
        void setPoints(const std::vector<sf::Vector2f>& localPoints);

    private:
        void updateCacheIfNeeded() const;
        void updateCache() const;
        bool isSelfIntersecting() const;
    
        std::vector<sf::Vector2f> m_localPoints; ///< Points relative to bounding box (0,0)
        mutable std::vector<sf::Vector2f> m_transformedPoints; ///< Cached transformed points
    
        mutable float m_perimeterCached;
        mutable float m_areaCached;
        mutable sf::Vector2f m_centroidCached;
        mutable sf::FloatRect m_boundsCached;

        ///Is the transformCache still valid
        mutable sf::Transform m_transformCache;
        mutable bool m_valid;

};


#endif // POLYGON_HPP
