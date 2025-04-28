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

/// @brief Draw the polygon with it's color and thickness.
/// @param target 
/// @param states 
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
    //std::cout << "Drawing polygon ->\n";
    for (std::size_t idx = 0; idx < n; idx++)
    {
        // Index of the next vertex
        std::size_t jdx = (idx + 1 == n ? 0 : idx + 1);
        sf::Vector2f p1 = m_vertices[idx].position;
        sf::Vector2f p2 = m_vertices[jdx].position;
        //std::cout << "    (" << p1.x << ", " << p1.y << ")";
        //std::cout << " to (" << p2.x << ", " << p2.y << ")";

        // Direction vector between the points
        sf::Vector2f direction = p2 - p1;
        //std::cout << "\n        Dir - (" << direction.x << ", " << direction.y << ")";

        // Compute unit normal (normalized vector perpendicular to the edge)
        sf::Vector2f normal = Vec2::normalize(Vec2::perp(direction));
        //std::cout << "\n        Norm - (" << normal.x << ", " << normal.y << ")";

        // Calculate the midpoint between p1 and p2
        sf::Vector2f midpoint = (p1 + p2) / 2.0f;
        //std::cout << "\n        Mid - (" << midpoint.x << ", " << midpoint.y << ")";
        

        // Set size and position for the rectangle representing the edge
        float length = Vec2::length(direction);
        edgeRect.setSize({length, m_thickness});  // Set size to match edge length and thickness
        //std::cout << "\n        Size- (" << length << ", " << m_thickness << ")";
        


        // Set origin to the center of the rectangle
        edgeRect.setOrigin(length / 2, m_thickness / 2);

        // Set the position to the midpoint of the edge
        edgeRect.setPosition(midpoint);

        // Set rotation to align with the direction of the edge
        edgeRect.setRotation(Vec2::angleOf(direction) * 180 / M_PI);

        // Draw the edge
        target.draw(edgeRect, states);
        //std::cout << '\n';
    }
}

bool Polygon::contains(const sf::Vector2f& point) const
{
    bool inside = false;
    size_t count = m_vertices.getVertexCount();
    
    if (count < 3) return false; // Not a valid polygon (must have at least 3 points)

    // Loop through each edge of the polygon. 
    //We need to determine how many edges a ray in one direction (right) crosses.
    //If it is odd, we are inside the shape.
    //If it is even, we are outside
    for (size_t idx = 0; idx < count; idx++)
    {
        // Get the current vertex and the next vertex (wrapping around at the end)
        sf::Vector2f vertexI = getTransform().transformPoint(m_vertices[idx].position);
        sf::Vector2f vertexJ = getTransform().transformPoint(m_vertices[(idx + 1) % count].position);

        // Check if the ray from the point crosses the edge at this y-coordinate
        bool isAbovePointI = (vertexI.y > point.y);  // Is vertex I above the point?
        bool isAbovePointJ = (vertexJ.y > point.y);  // Is vertex J above the point?

        // Check if one vertex is above and the other is below (ray crosses edge)
        bool crossesYLine = isAbovePointI != isAbovePointJ;

        // Calculate the x-coordinate of the intersection point between the ray and the edge
        float intersectionX = (vertexJ.x - vertexI.x) * (point.y - vertexI.y) / (vertexJ.y - vertexI.y) + vertexI.x;

        // Check if the point's x-coordinate is to the left of the intersection point
        bool isLeftOfIntersection = point.x < intersectionX;

        // Final check: does the ray cross the edge, and is the intersection to the right of the point?
        bool intersect = crossesYLine && isLeftOfIntersection;

        if (intersect)
        {
            inside = !inside; // Flip inside status whenever we cross an edge
        }
    }

    return inside;
}