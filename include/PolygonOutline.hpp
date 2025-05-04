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

class PolygonOutline : public sf::Drawable
{
public:
    PolygonOutline(const Polygon& polygon, sf::Color color = sf::Color::Red, float thickness = 1.0f);

    void update(); // Call when the polygon's position/rotation changes

    void setColor(sf::Color newColor);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const Polygon& polygon;
    sf::VertexArray outline;
    sf::Color color;
};

#endif // POLYGON_OUTLINE_HPP
