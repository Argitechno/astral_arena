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

#include "Polygon.hpp"

/// @brief Init the vertices to the points given, init thicnkess.
/// @param points 
Polygon::Polygon(const std::vector<sf::Vector2f>& points)
: m_vertices(sf::LineStrip, points.size())
, m_thickness(1.f)
{
    setPoints(points);
}

/// @brief set our vertice points to the given vector of points, and all to the current outline color
/// @param points 
void Polygon::setPoints(const std::vector<sf::Vector2f>& points)
{
    std::size_t n = points.size();
    // Resize our vertex array to match the new point count.
    m_vertices.resize(n);

    // Copy point positions into the vertices positions
    for (std::size_t idx = 0; idx < n; idx++)
    {
        m_vertices[idx].position = points[idx];
        m_vertices[idx].color    = m_outlineColor;  // use stored color
    }
}

/// @brief Get the vertex array
/// @return 
const sf::VertexArray& Polygon::getVertices() const
{
    return m_vertices;
}

/// @brief Update internal outline color variable, update each vertex's color.
/// @param c 
void Polygon::setOutlineColor(const sf::Color& c)
{
    m_outlineColor = c;
    
    for (std::size_t idx = 0; idx < m_vertices.getVertexCount(); idx++)
    {
        m_vertices[idx].color = m_outlineColor;
    }
}

/// @brief Update internal thickness variable
/// @param t 
void Polygon::setOutlineThickness(float t)
{
    m_thickness = t;
}

/// @brief Get internal thickness variable
/// @return 
float Polygon::getOutlineThickness() const
{
    return m_thickness;
}

void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    // We will draw a rectangle for each edge, with the given thickness.
    sf::RectangleShape edgeRect;
    edgeRect.setFillColor(m_outlineColor);

    std::size_t n = m_vertices.getVertexCount();
    if (n < 2)
    {
        return;
    }
    std::cout << "Drawing polygon ->\n";
    for (std::size_t idx = 0; idx < n; idx++)
    {
        // Index of the next vertex
        std::size_t jdx = (idx + 1 == n ? 0 : idx + 1);
        sf::Vector2f p1 = m_vertices[idx].position;
        sf::Vector2f p2 = m_vertices[jdx].position;
        std::cout << "    (" << p1.x << ", " << p1.y << ")";
        std::cout << " to (" << p2.x << ", " << p2.y << ")";

        // Direction vector between the points
        sf::Vector2f direction = p2 - p1;
        std::cout << "\n        Dir - (" << direction.x << ", " << direction.y << ")";

        // Compute unit normal (normalized vector perpendicular to the edge)
        sf::Vector2f normal = Vec2::normalize(Vec2::perp(direction));
        std::cout << "\n        Norm - (" << normal.x << ", " << normal.y << ")";

        // Calculate the midpoint between p1 and p2
        sf::Vector2f midpoint = (p1 + p2) / 2.0f;
        std::cout << "\n        Mid - (" << midpoint.x << ", " << midpoint.y << ")";
        

        // Set size and position for the rectangle representing the edge
        float length = Vec2::length(direction);
        edgeRect.setSize({length, m_thickness});  // Set size to match edge length and thickness
        std::cout << "\n        Size- (" << length << ", " << m_thickness << ")";
        


        // Set origin to the center of the rectangle
        edgeRect.setOrigin(length / 2, m_thickness / 2);

        // Set the position to the midpoint of the edge
        edgeRect.setPosition(midpoint);

        // Set rotation to align with the direction of the edge
        edgeRect.setRotation(Vec2::angleOf(direction) * 180 / M_PI);

        // Draw the edge
        target.draw(edgeRect, states);
        std::cout << '\n';
    }
}
