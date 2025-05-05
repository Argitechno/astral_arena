/// ->
/// * @file DebugDrawer.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief Drawer (Mainly for debug) to be used on IShapes. Rn that is only Polygon
/// * @version 0.1
/// * @date 2025-05-04
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#ifndef DEBUGDRAWER_HPP
#define DEBUGDRAWER_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "IShape.hpp"
#include "Polygon.hpp"

class DebugDrawer : public GameObject, public sf::Drawable
{
    public:
        /// ->
        /// * @brief Constructor to initialize the DebugDrawer with an IShape pointer (e.g., Polygon)
        /// * 
        /// * @param shape 
        /// <-
        DebugDrawer(const IShape* shape);

        /// ->
        /// * @brief Method to set the color of the bounding box
        /// * 
        /// * @param color 
        /// <-
        void setBoundingBoxColor(const sf::Color& color);

        /// ->
        /// * @brief Method to set the color of the centroid
        /// * 
        /// * @param color 
        /// <-
        void setCentroidColor(const sf::Color& color);

        /// ->
        /// * @brief Override the update method from GameObject
        /// * 
        /// * @param deltaTime 
        /// <-
        void update(float deltaTime) override;

protected:
    
    /// ->
    /// * @brief Override the draw method to render the bounding box and centroid
    /// * 
    /// * @param target 
    /// * @param states 
    /// <-
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    /// ->
    /// * @brief Pointer to the IShape (abstract base class for shapes)
    /// * 
    /// <-
    const IShape* shapePtr;

    /// ->
    /// * @brief For drawing bounding box
    /// * 
    /// <-
    sf::RectangleShape boundingBox;

    /// ->
    /// * @brief For drawing centroid
    /// * 
    /// <-
    sf::CircleShape centroidCircle;
};

#endif // DEBUGDRAWER_HPP
