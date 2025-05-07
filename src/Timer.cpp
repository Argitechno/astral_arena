#include "Timer.hpp"

Timer::Timer() : elapsedTime(0.0f), interval(1.0f) {}  // Constructor initialization list

Timer::~Timer() {
    // Destructor can be used for cleanup, if necessary (none in this case)
}

void Timer::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= interval) {
        std::cout << "One second passed!" << std::endl;
        elapsedTime = 0.0f;  // Reset elapsed time
    }
}