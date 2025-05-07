/// ->
/// * @file PolygonOutline.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-05-02
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#if !defined(POLYGON_OUTLINE_HPP)
#define POLYGON_OUTLINE_HPP

#include <SFML/Graphics.hpp>
#include "Polygon.hpp"
#include "GameObject.hpp"

class PolygonOutline : public GameObject, public sf::Drawable
{
    public:
        // Constructor that initializes the outline with a polygon, color, and thickness
        PolygonOutline(const Polygon* polygon, sf::Color color = sf::Color::Red, float thickness = 1.0f);

        // Update method to be called when the polygon's position/rotation changes
        virtual void update(float deltaTime) override;

        // Set the outline's color
        void setColor(sf::Color newColor);

        sf::Color getColor() const;

    private:
        // Draw method to render the outline
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        const Polygon* polygon;  // Reference to the polygon that represents the hitbox
        sf::VertexArray outline;  // SFML vertex array for the outline
        sf::Color color;  // Color of the outline
        float thickness;  // Thickness of the outline
};

#endif // POLYGON_OUTLINE_HPP
