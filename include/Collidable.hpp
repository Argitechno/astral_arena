/// ->
/// * @file Collidable.hpp
/// * @author Caleb Blondell (crblondell@nic.edu)
/// * @brief 
/// * @version 0.1
/// * @date 2025-05-05
/// * 
/// * @copyright Copyright (c) 2025
/// * 
/// <-
#if !defined(COLLIDABLE_HPP)
#define COLLIDABLE_HPP

enum class CollisionStatus {
    None,         // No contact at all
    Touching,     // Just touching edges or vertices
    Overlapping,  // Partial overlap
    Contained     // One is fully inside the other
};

enum class CollisionType {
    None,
    Border,
    Spaceship,
    Obstacle
};

class Collidable
{
    public:
        

        /// @brief Default destructor
        virtual ~Collidable() = default;

        /// @brief Returns the type of collision if the shapes intersect.
        /// @param other 
        /// @return 
        virtual CollisionStatus intersects(const Collidable& other) const = 0;

        // Get the collision type for this object
        inline CollisionType getCollisionType() const
        {
            return m_collisionType;
        }

        // Set the collision type for this object
        inline void setCollisionType(CollisionType collisionType)
        {
            m_collisionType = collisionType;
        }

    protected:
        /// @brief Default constructor sets a default collision type
        Collidable(CollisionType collisionType = CollisionType::None) : m_collisionType(collisionType){}

    private:
        CollisionType m_collisionType;
};

#endif // COLLIDABLE_HPP
