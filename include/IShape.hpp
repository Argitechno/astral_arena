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

#ifndef I_SHAPE_HPP
#define I_SHAPE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

/// @brief A shape is that which 'defines the outline or boundary of an object'.
///        So what a shape would allow is seeing if something inside, or outside of it.
///        What it's area is.
///        And the length of the enclosing boundary (perimiter)
class IShape : public sf::Transformable{
    public:
        /// @brief Default destructor, no constructor because we are an interface.
        virtual ~IShape() = default;

        /// @brief Does this shape contain a point?
        /// @param point 
        /// @return 
        virtual bool contains(const sf::Vector2f& point) const = 0;

        /// @brief What is the area if this shape?
        /// @return 
        virtual float getArea() const = 0;

        /// @brief What is the length of this shapes boundary?
        /// @return 
        virtual float getPerimeter() const = 0;

        /// @brief What is the geometric center point of this shape?
        /// @return 
        virtual sf::Vector2f getCentroid() const = 0;

        /// @brief What is the smallest rectangle in which this shape can fit? Has to recalc bounds if tranform changes.
        /// @return 
        virtual sf::FloatRect getBounds() const = 0;
};


#endif // I_SHAPE_HPP
