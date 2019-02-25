//
// Created by samip on 12/2/19.
//To use this, instantiate the remainTime with the total time as constructor argument. And call, getRemainTime() to get the remaining time in min:sec format.
//

#pragma once


#include <SFML/System/Clock.hpp>
#include <iostream>
class remainTime {
private:
    int elapsedSeconds;
    int elapsedMinutes;
    int totalSeconds;
    sf::Clock clock;
public:
    remainTime(int i):elapsedSeconds(0),elapsedMinutes(0),totalSeconds(i){}
    int getRemainSeconds();
    int getRemainMinutes();
    std::string getRemainTime();
};
