/// ->
/// * @file PolygonOutline.cpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-05-02
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#include "PolygonOutline.hpp"

PolygonOutline::PolygonOutline(const Polygon* poly, sf::Color color, float thickness)
    : polygon(poly), color(color), outline(sf::LineStrip)
{
    update(0.f);  // Initialize outline
}

void PolygonOutline::update(float deltaTime)
{
    // Assuming getPoints() returns the transformed points (position + rotation) of the polygon
    const std::vector<sf::Vector2f>& points = (*polygon).getPoints(); 
    outline.clear();

    // Append each point of the polygon to the outline
    for (std::size_t i = 0; i < points.size(); ++i)
    {
        outline.append(sf::Vertex(points[i], color));
    }

    // Close the loop by appending the first point again
    if (!points.empty())
    {
        outline.append(sf::Vertex(points[0], color));
    }
}

void PolygonOutline::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(outline, states);
}

void PolygonOutline::setColor(sf::Color newColor)
{
    color = newColor;

    for (std::size_t i = 0; i < outline.getVertexCount(); ++i)
    {
        outline[i].color = color;
    }
}