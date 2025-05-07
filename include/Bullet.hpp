/// ->
/// * @file Bullet.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief Define a spaceship - movement physics
/// * @version 0.2
/// * @date 2025-05-04
/// * 
/// * @copyright Copyright (c) 2025
/// <-

#if !defined(BULLET_HPP)
#define BULLET_HPP

#include "GameObject.hpp"
#include "Polygon.hpp"
#include "PolygonOutline.hpp"
#include <SFML/Graphics.hpp>

/// ->
/// * @brief Configuration for spaceship physics and behavior.
/// <-
struct BulletConfig
{
    float acceleration = 360.f;        ///< Linear acceleration when thrust is applied
    float maxSpeed = 360.f;            ///< Maximum forward speed
    float linearDamping = 0.4f;       ///< Damping factor for forward velocity

    float angularAcceleration = 611.f;              ///< Angular acceleration when torque is applied
    float maxAngularSpeed = 306.f;
    float angularDamping = 0.5f;      ///< Damping factor for angular velocity
};

class Bullet : public GameObject, public sf::Drawable
{
    public:
        /// ->
        /// * @brief Construct a new Bullet object using a polygon as the shape.
        /// *        Optional rotation/position offsets and config can be passed.
        /// * 
        /// * @param initialRotation Initial rotation of ship.
        /// * @param initialPosition Initial position of ship.
        /// * @param config Optional spaceship config
        /// <-
        Bullet
        (
            float initialRotation = 0.f,
            const sf::Vector2f& initialPosition = {0.f, 0.f},
            const BulletConfig& config = BulletConfig{}
        );

        /// ->
        /// * @brief Update the spaceship.
        /// * 
        /// * @param deltaTime Time since last frame
        /// <-
        void update(float deltaTime) override;

        /// @brief We draw the spaceship's polygon outline
        /// @param target 
        /// @param states 
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        /// @brief reset the bullet to transparent and nonmoving at 0,0
        void reset();

        /// ->
        /// * @brief Set the spaceship's position
        /// * 
        /// * @param pos 
        /// <-
        void setPosition(const sf::Vector2f& pos);

        /// ->
        /// * @brief Set the spaceship's rotation
        /// * 
        /// * @param angle 
        /// <-
        void setRotation(float angle);

        /// ->
        /// * @brief Get the spaceship's current position
        /// * 
        /// * @return sf::Vector2f 
        /// <-
        sf::Vector2f getPosition() const;

        /// ->
        /// * @brief Get the spaceship's current rotation
        /// * 
        /// * @return float 
        /// <-
        float getRotation() const;

        /// ->
        /// * @brief Set the spaceship's velocity
        /// * 
        /// * @param vel 
        /// <-
        void setVelocity(const sf::Vector2f& vel);

        /// ->
        /// * @brief Get the spaceship's current velocity
        /// * 
        /// * @return const sf::Vector2f& 
        /// <-
        const sf::Vector2f& getVelocity() const;

        /// ->
        /// * @brief Get the spaceship's angular velocity
        /// * 
        /// * @return float 
        /// <-
        float getAngularVelocity() const;

        /// ->
        /// * @brief Get the spaceship's hitbox (polygon)
        /// * 
        /// * @return const Polygon& 
        /// <-
        const Polygon& getHitbox() const;

        /// ->
        /// * @brief Set the color of the spaceship's outline
        /// * 
        /// * @param color 
        /// <-
        void setColor(const sf::Color& color);

        /// ->
        /// * @brief Get the spaceship's configuration (accel, damping, etc.)
        /// * 
        /// * @return const BulletConfig& 
        /// <-
        const BulletConfig& getConfig() const;

        /// ->
        /// * @brief Set the spaceship's configuration
        /// * 
        /// * @param config 
        /// <-
        void setConfig(const BulletConfig& config);

        /// @brief shoot bullet from a position with a velocity, and a color
        void shoot(sf::Vector2f position, sf::Vector2f velocity, sf::Color color);

        /// @brief return if this bullet is currently shot.
        bool getShot() const;

    private:
        sf::Vector2f m_position;
        float m_rotation = 0.f;

        sf::Vector2f m_velocity{};

        bool m_shot;
        float m_shotTimer;

        Polygon m_hitbox;
        PolygonOutline m_outline;

        BulletConfig m_config;

        void syncTransforms();
};

#endif // BULLET_HPP
