//
// Created by samip on 12/2/19.
//

#include "RemainTime.h"
#include <sstream>
int remainTime::getRemainSeconds()
{
    elapsedSeconds = static_cast<unsigned int>(clock.getElapsedTime().asSeconds());
    return (totalSeconds-elapsedSeconds)%60;
}
int remainTime::getRemainMinutes()
{
    int totalMinutes = totalSeconds/60;
    elapsedMinutes = static_cast<int>(clock.getElapsedTime().asSeconds())/60+1;
    if(static_cast<int>(clock.getElapsedTime().asSeconds())%60==0)
        elapsedMinutes--;
    return (totalMinutes-elapsedMinutes);
}
std::string remainTime::getRemainTime()
{
    std::stringstream time;
    time<<this->getRemainMinutes()<<":"<<this->getRemainSeconds();
    return time.str();
}
