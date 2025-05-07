/// ->
/// * @file Spaceship.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief Define a spaceship - movement physics
/// * @version 0.2
/// * @date 2025-05-04
/// * 
/// * @copyright Copyright (c) 2025
/// <-

#if !defined(SPACESHIP_HPP)
#define SPACESHIP_HPP

#include "GameObject.hpp"
#include "Bullet.hpp"
#include "Polygon.hpp"
#include "PolygonOutline.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <array>


/// ->
/// * @brief Configuration for spaceship physics and behavior.
/// <-
struct SpaceshipConfig
{
    float acceleration = 360.f;        ///< Linear acceleration when thrust is applied
    float maxSpeed = 360.f;            ///< Maximum forward speed
    float linearDamping = 0.4f;       ///< Damping factor for forward velocity

    float angularAcceleration = 611.f;              ///< Angular acceleration when torque is applied
    float maxAngularSpeed = 306.f;
    float angularDamping = 0.5f;      ///< Damping factor for angular velocity
};

class Spaceship : public GameObject, public sf::Drawable
{
    public:
        /// ->
        /// * @brief Construct a new Spaceship object using a polygon as the shape.
        /// *        Optional rotation/position offsets and config can be passed.
        /// * 
        /// * @param initialRotation Initial rotation of ship.
        /// * @param initialPosition Initial position of ship.
        /// * @param config Optional spaceship config
        /// <-
        Spaceship
        (
            float initialRotation = 0.f,
            const sf::Vector2f& initialPosition = {0.f, 0.f},
            const SpaceshipConfig& config = SpaceshipConfig{}
        );

        /// @brief Apply forward thrust to the spaceship next update
        void applyThrust();

        /// @brief Apply rotational torque to the spaceship (positive or negative) next update
        /// @param direction 1 for CW, 0 for CCW
        void applyTorque(bool direction);

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

        /// @brief Set the angular velocity of the spaceship
        /// @param angVel 
        void setAngularVelocity(float angVel);

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
        /// * @return const SpaceshipConfig& 
        /// <-
        const SpaceshipConfig& getConfig() const;

        /// ->
        /// * @brief Set the spaceship's configuration
        /// * 
        /// * @param config 
        /// <-
        void setConfig(const SpaceshipConfig& config);

        /// @brief If we have any bullets left, we shoot it out. Bullets will come back after 1 second, or when they hit something.
        void shoot();

        /// @brief get the color our outline is set to.
        sf::Color getColor() const;

    private:
        sf::Vector2f m_position;
        float m_rotation = 0.f;

        sf::Vector2f m_velocity{};
        float m_angularVelocity = 0.f;

        Polygon m_hitbox;
        PolygonOutline m_outline;

        SpaceshipConfig m_config;
        float m_shootCooldown = 0.f;
        const float m_minShootDelay = 0.2f;

        /// @brief Maximum 5 bullets allowed.
        std::array<Bullet, 5> m_bullets;

        bool m_thrustApplied = false;
        std::optional<bool> m_torqueDirection = std::nullopt;

        void limitSpeed();
        void syncTransforms();
};

#endif // SPACESHIP_HPP
