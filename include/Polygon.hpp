/// ->
/// * @file Polygon.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief Define the structure of polygon
/// * @version 0.1
/// * @date 2025-04-28
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#include "GameObject.hpp"
#include "VectorUtils.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


#ifndef POLYGON_HPP
#define POLYGON_HPP

/// @brief A general outlined polygon; stores its points in an sf::VertexArray.
class Polygon : public GameObject, public sf::Drawable, public sf::Transformable {
    public:
        /// @param points  Initial vertices (in local space).  
        explicit Polygon(const std::vector<sf::Vector2f>& points);

        /// @brief Override the virtual destructor from GameObject with default.
        ~Polygon() override = default;

        /// @brief Polygon by itself has no need to update. Future inherited classes might.
        /// @param deltaTime 
        void update(float deltaTime) override { /* no-op */ }

        /// @brief Replace all vertices
        /// @param points 
        void setPoints(const std::vector<sf::Vector2f>& points);
    
        /// @brief Access the raw vertex array for collision/tests/etc.
        /// @return The vertex array
        const sf::VertexArray& getVertices() const;

        /// @brief Set each vertex to a color
        /// @param c 
        void setOutlineColor(const sf::Color& c);

        /// @brief Set the polygons outline thickness
        /// @param t 
        void setOutlineThickness(float t);

        /// @brief Get the polygon's outline thickness
        /// @return 
        float getOutlineThickness() const;
    
    protected:
        /// @brief SFML calls this with window.draw(polygon), which we do with GameManager
        /// @param target 
        /// @param states 
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    private:
        /// @brief Hold the vertices of the polygon
        sf::VertexArray m_vertices;
        
        /// @brief To edit the thickness of the line (visual)
        float           m_thickness;
        
        /// @brief The color of our outline (each vertex)
        sf::Color       m_outlineColor;
    };

#endif