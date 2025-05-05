#include "DebugDrawer.hpp"
#include <stdexcept>  // For std::runtime_error

/// Constructor implementation
DebugDrawer::DebugDrawer(const IShape* shape) :
    shapePtr(shape)
{
    // If the shape is not a Polygon, throw an exception (for now)
    if (dynamic_cast<const Polygon*>(shapePtr) == nullptr)
    {
        throw std::runtime_error("DebugDrawer currently only supports Polygon shapes.");
    }

    // If it's a Polygon, initialize the bounding box and centroid for it
    const Polygon* polygon = dynamic_cast<const Polygon*>(shapePtr);

    centroidCircle.setRadius(5.f);
    centroidCircle.setFillColor(sf::Color::Red);
    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOutlineColor(sf::Color::Green);
    boundingBox.setOutlineThickness(2.f);

    update(0.f);  // Initialize bounding box and centroid
}

/// Method to set the color of the bounding box
void DebugDrawer::setBoundingBoxColor(const sf::Color& color)
{
    boundingBox.setOutlineColor(color);
}

/// Method to set the color of the centroid
void DebugDrawer::setCentroidColor(const sf::Color& color)
{
    centroidCircle.setFillColor(color);
}

/// Override the update method from GameObject
void DebugDrawer::update(float deltaTime)
{
    // Update the bounding box and centroid based on the shape
    const Polygon* polygon = dynamic_cast<const Polygon*>(shapePtr);
    if (polygon)
    {
        sf::FloatRect bounds = polygon->getBounds();
        boundingBox.setSize(sf::Vector2f(bounds.width, bounds.height));
        boundingBox.setPosition(bounds.left, bounds.top);

        // Update centroid position
        sf::Vector2f centroid = polygon->getCentroid();
        centroidCircle.setPosition(centroid);
    }
}

void DebugDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(boundingBox, states);
    target.draw(centroidCircle, states);
}
