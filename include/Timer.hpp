#ifndef TIMER_HPP
#define TIMER_HPP

#include "GameObject.hpp"
#include <iostream>

class Timer : public GameObject {
    public:
        Timer();  // Constructor declaration
        virtual ~Timer();  // Destructor declaration

        void update(float deltaTime) override;  // Override the update method

    private:
        float elapsedTime;  // Tracks the elapsed time
        const float interval;  // Interval at which to print the message (1 second)
};

#endif
    