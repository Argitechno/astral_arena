/// ->
/// * @file Bullet.cpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-05-07
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#include "Bullet.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <limits>
#include <iostream>
#include "VectorUtils.hpp"



Bullet::Bullet
(   
    float initialRotation,
    const sf::Vector2f& initialPosition,
    const BulletConfig& config
) :
    m_config(config),
    m_outline(&m_hitbox, sf::Color::Transparent),
    m_shot(false),
    m_shotTimer(0.f)
{
    ///Define the shape, could pass in a polygon, but too late at this point to allow such.
    Polygon shape;
    shape.addPoint({30.f, 10.f});
    shape.addPoint({15.f, 45.f});
    shape.addPoint({45.f, 45.f});
    shape.setScale(0.2, 0.2);
    m_hitbox = shape;
    // Apply initial transformation to hitbox
    m_hitbox.rotate(90.0f);

    std::vector<sf::Vector2f> points = m_hitbox.getPoints();
    size_t count = points.size();
    float minX = std::numeric_limits<float>::infinity();
    float minY = std::numeric_limits<float>::infinity();
    for(size_t idx = 0; idx < count; idx++)
    {
        if(points[idx].x < minX)
        {
            minX = points[idx].x;
        }
        if(points[idx].y < minY)
        {
            minY = points[idx].y;
        }
    }
    for(size_t idx = 0; idx < count; idx++)
    {
        points[idx].x -= minX;
        points[idx].y -= minY;
    }

    m_hitbox = Polygon(points);
    m_hitbox.setOrigin(m_hitbox.getCentroid());
    setRotation(initialRotation);
    setPosition(initialPosition);
    m_outline.update(0.f);
}

/// @brief reset the bullet to transparent and nonmoving at 0,0
void Bullet::reset()
{
    m_shot = false;
    m_shotTimer = 0;
    m_outline.setColor(sf::Color::Transparent);
    setPosition({0.f, 0.f});
    setVelocity({0.f, 0.f});
    setRotation(0.f);
}

/// @brief Shoot the bullet from a position with a certain velocity and color. Flag as shot so that we can start timer and reset after 1s.
void Bullet::shoot(sf::Vector2f position, sf::Vector2f velocity, sf::Color color)
{
    if(!m_shot)
    {
        m_shot = true;
        std::cout << "Shooting Bullet!\n";
        std::cout << "   Dir = " << Vec2::angleOf(velocity) << '\n';
        std::cout << "   Pos = (" << position.x << ", " << position.y << ")\n";
        std::cout << "   Vel = (" << velocity.x << ", " << velocity.y << ")\n";
        std::cout << "   Col = (" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ")\n";
        std::cout << "   BulletShot: " << m_shot << '\n';
        m_outline.setColor(color);
        setPosition(position);
        setVelocity(velocity);
        setRotation(Vec2::radiansToDegrees(Vec2::angleOf(velocity)));
        
    }
}

void Bullet::setVelocity(const sf::Vector2f& vel)
{
    m_velocity = vel;
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_outline, states);
}

void Bullet::update(float deltaTime)
{
    //std::cout << "Bullet Shot: " << m_shot << " dt = " << deltaTime << " timer = " << m_shotTimer << '\n';
    
    if(m_shot)
    {
        //std::cout << "Adding DeltaTime";
        m_shotTimer += deltaTime;
    }
    if(m_shotTimer > 3.f)
    {
        //std::cout << "Reset Bullet!";
        reset();
    }
    // Update position
    setPosition(getPosition() + m_velocity * deltaTime);
    // Reset flags
}

void Bullet::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;
    syncTransforms();
}

void Bullet::setRotation(float angle)
{
    m_rotation = angle;
    syncTransforms();
}

sf::Vector2f Bullet::getPosition() const
{
    return m_position;
}

const sf::Vector2f& Bullet::getVelocity() const
{
    return m_velocity;
}

const Polygon& Bullet::getHitbox() const
{
    return m_hitbox;
}

void Bullet::setColor(const sf::Color& color)
{
    m_outline.setColor(color);
}

const BulletConfig& Bullet::getConfig() const
{
    return m_config;
}

void Bullet::setConfig(const BulletConfig& config)
{
    m_config = config;
}

void Bullet::syncTransforms()
{
    m_hitbox.setPosition(m_position);
    m_hitbox.setRotation(m_rotation);
    m_outline.update(0.f);
}

bool Bullet::getShot() const
{
    return(m_shot);
}
