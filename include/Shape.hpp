/// ->
/// * @file Shape.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief We define a shape with as basic as possible definitions, and each method answers a question about a shape.
/// * @version 0.1
/// * @date 2025-04-29
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

/// @brief Shapes we will implement
enum class ShapeType 
{
    Circle, 
    Polygon, 
    Complex
};

/// @brief A shape is that which 'defines the outline or boundary of an object'.
///        So what a shape would allow is seeing if something inside, or outside of it.
///        What it's area is.
///        And the length of the enclosing boundary (perimiter)
class IShape : public sf::Transformable {
public:
    /// @brief Default destructor, no constructor because we are an interface.
    virtual ~IShape() = default;

    /// @brief Does this shape contain a point?
    /// @param point 
    /// @return 
    virtual bool contains(const sf::Vector2f& point) const = 0;

    /// @brief What is the area if this shape?
    /// @return 
    virtual float area() const = 0;

    /// @brief What is the length of this shapes boundary?
    /// @return 
    virtual float perimeter() const = 0;

    /// @brief What is the type of this shape?
    /// @return 
    virtual ShapeType type() const = 0;

    /// @brief What is the geometric point of this shape?
    /// @return 
    virtual sf::Vector2f centroid() const = 0;

    /// @brief What is the smallest rectangle in which this shape can fit?
    /// @return 
    virtual sf::FloatRect bounds() const = 0;

    /// @brief Does this shape intersect another shape?
    /// @param other 
    /// @return 
    virtual bool intersects(const IShape& other) const = 0;
};

#endif // SHAPE_HPP
