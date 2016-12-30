/**
 * this class defines a Clock, that indicates the time of the world.
 */

#include "Clock.h"

/**
 * a constructor of the clock, initialized to 0.
 */
Clock::Clock() {
    this->currentTime = 0;
}

/**
 * a destructor of the clock.
 */
Clock::~Clock() {
}

/**
 * this function returns the current time of the world.
 * @return the current time.
 */
int Clock::getCurrentTime() {
    return this->currentTime;
}

/**
 * this function updates the time of the world by 1.
 */
void Clock::updateTime() {
    this->currentTime++;
}