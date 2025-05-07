/// ->
/// * @file Spaceship.cpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief Define a spaceship - movement physics
/// * @version 0.1
/// * @date 2025-05-04
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-

#include "Spaceship.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <limits>
#include <iostream>
#include "VectorUtils.hpp"

Spaceship::Spaceship
(   
    float initialRotation,
    const sf::Vector2f& initialPosition,
    const SpaceshipConfig& config
) :
    m_config(config),
    m_outline(&m_hitbox)
{
    ///Define the shape, could pass in a polygon, but too late at this point to allow such.
    Polygon shape;
    shape.addPoint({30.f, 10.f});
    shape.addPoint({15.f, 45.f});
    shape.addPoint({45.f, 45.f});
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

void Spaceship::applyThrust()
{
    if(!m_thrustApplied){
        m_thrustApplied = true;
    }
}

void Spaceship::applyTorque(bool direction)
{
    m_torqueDirection = direction;
}

void Spaceship::update(float deltaTime)
{
    m_shootCooldown += deltaTime;

    for(size_t idx = 0; idx < 5; idx++)
    {
       Bullet* bullet = &m_bullets[idx];
       bullet->update(deltaTime);
    }


    // Apply angular acceleration if torque is applied
    if (m_torqueDirection.has_value()) {
        float torque = m_config.angularAcceleration * deltaTime;
        if (*m_torqueDirection)
            m_angularVelocity += torque;  // right turn
        else
            m_angularVelocity -= torque;  // left turn
    }

    // Clamp angular velocity
    if (std::abs(m_angularVelocity) > m_config.maxAngularSpeed) {
        m_angularVelocity = m_config.maxAngularSpeed * (m_angularVelocity > 0 ? 1.f : -1.f);
    }

   if (!m_torqueDirection.has_value())
   {
        if (std::abs(m_angularVelocity) < 5.f)
        {
            m_angularVelocity = 0.f;
        }
   }
    // Apply angular damping
    m_angularVelocity *= std::pow(1.f - m_config.angularDamping, deltaTime);
    

    // Update rotation
    setRotation(getRotation() + m_angularVelocity * deltaTime);

    // Apply thrust if flagged
    if (m_thrustApplied) {
        float angleRad = m_rotation * (3.14159265f / 180.f);
        sf::Vector2f direction(std::cos(angleRad), std::sin(angleRad));
        m_velocity += direction * m_config.acceleration * deltaTime;
    }

    // Clamp linear speed
    float speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (speed > m_config.maxSpeed) {
        m_velocity *= m_config.maxSpeed / speed;
    }

    // Apply linear damping
    m_velocity *= std::pow(1.f - m_config.linearDamping, deltaTime);
    if(!m_thrustApplied)
    {
        if (Vec2::length(m_velocity) < 5.f)
        {
            m_velocity = {0, 0};
        }
    }

    // Update position
    setPosition(getPosition() + m_velocity * deltaTime);

    // Reset flags
    m_torqueDirection.reset();
    m_thrustApplied = false;
}

void Spaceship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(size_t idx = 0; idx < 5; idx++)
    {
        const Bullet* bullet = &m_bullets[idx];
        target.draw(*bullet, states);
    }
    target.draw(m_outline, states);
}

void Spaceship::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;
    syncTransforms();
}

void Spaceship::setRotation(float angle)
{
    m_rotation = angle;
    syncTransforms();
}

sf::Vector2f Spaceship::getPosition() const
{
    return m_position;
}

float Spaceship::getRotation() const
{
    return m_rotation;
}

void Spaceship::setVelocity(const sf::Vector2f& vel)
{
    m_velocity = vel;
}

void Spaceship::setAngularVelocity(float angVel)
{
    m_angularVelocity = angVel;
}

const sf::Vector2f& Spaceship::getVelocity() const
{
    return m_velocity;
}

float Spaceship::getAngularVelocity() const
{
    return m_angularVelocity;
}

const Polygon& Spaceship::getHitbox() const
{
    return m_hitbox;
}

void Spaceship::setColor(const sf::Color& color)
{
    m_outline.setColor(color);
}

const SpaceshipConfig& Spaceship::getConfig() const
{
    return m_config;
}

void Spaceship::setConfig(const SpaceshipConfig& config)
{
    m_config = config;
}

void Spaceship::limitSpeed()
{
    float speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (speed > m_config.maxSpeed)
    {
        m_velocity *= m_config.maxSpeed / speed;
    }
}

void Spaceship::syncTransforms()
{
    m_hitbox.setPosition(m_position);
    m_hitbox.setRotation(m_rotation);
    m_outline.update(0.f);
}

sf::Color Spaceship::getColor() const
{
    return m_outline.getColor();
}

void Spaceship::shoot()
{   
    if(m_shootCooldown < m_minShootDelay)
    {
        return;
    }
    m_shootCooldown = 0;
    for(size_t idx = 0; idx < m_bullets.size(); idx++)
    {
        Bullet* bullet = &m_bullets[idx];
        if(!bullet->getShot())
        {
            float rotDeg = getRotation();
            float rotRad = Vec2::degreesToRadians(rotDeg);
            sf::Vector2f dir = {std::cos(rotRad), std::sin(rotRad)};
            sf::Vector2f offset = {dir.x * 10, dir.y * 10};
            sf::Vector2f velocity = {dir.x * 300, dir.y * 300};
            bullet->shoot(getPosition() + offset, velocity + getVelocity() , getColor());
            break;
        }
    }
    
}