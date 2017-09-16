//
//  TimeRemainder.cpp
//  当前时间-计时器
//
//  Created by Jaye Wang on 8/8/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#include "TimeRemainder.hpp"

/**
 Sample call: 没有偏差 for every single element
 
 tr::TimeRemainder timeLeft_tillFallBegin(9,25,2017,0,0,0,1, "距离Fall quater 2017 begin");
 
 since the old style time_t starting counting for 0 for some variable,
 
 
 tm_mon need to minus 1
 tm_year need to minus 1900
 .. see tm struct documentation.
 
 */

tr::TimeRemainder::TimeRemainder(const int& month, const int& day_of_month,
                             const int& year,  const int& hour,
                             const int& minutes, const int & seconds,
                             const int& isDaySavingTime,
                             const std::string& theMessage
                             )
{
    message = theMessage;
    now = time(0);
    target_time_tm.tm_mon = month - 1 ;
    target_time_tm.tm_mday = day_of_month;
    target_time_tm.tm_year = year - 1900;
    target_time_tm.tm_hour = hour;
    target_time_tm.tm_min = minutes;
    target_time_tm.tm_sec = seconds;
    target_time_tm.tm_isdst = isDaySavingTime;
    
    
    // Calculate the time until the final
    target_time_time_t = mktime(&target_time_tm);
    int seconds_till_Target_Time = difftime(target_time_time_t, now);
    
    daysRemainder = seconds_till_Target_Time/SECONDS_PER_DAY;
    hoursRemainder = (seconds_till_Target_Time
                      - daysRemainder* SECONDS_PER_DAY)/SECONDS_PER_HOUR;
    minutesRemainder =(seconds_till_Target_Time
                       - daysRemainder* SECONDS_PER_DAY- hoursRemainder*
                       SECONDS_PER_HOUR)/SECOND_PER_MINUTE;
    secondsRemainder = seconds_till_Target_Time
                        - daysRemainder* SECONDS_PER_DAY
                        - hoursRemainder*SECONDS_PER_HOUR
                        - minutesRemainder*SECOND_PER_MINUTE;
}

std::string tr::TimeRemainder::getCurrentTime() const
{
    std::string currentTime;
    
    
    return currentTime;
}

void tr::TimeRemainder::printCurrentTime()
{
    time_t now = time(0);
    
    //struct tm* timeInfo = localtime(&now);  // This is the old
    //version of C language style.
    tm* timeInfo = localtime(&now);
    
    std::cout << ""
    << std::setw(2)<< std::setfill('0') <<timeInfo->tm_mon + 1
    << '/' <<  std::setw(2)<< std::setfill('0')<< timeInfo->tm_mday
    << '/' << std::setw(2) << std::setfill('0')<<  timeInfo->tm_year % 100
    
    << ' ' << std::setw(2) << std::setfill('0')<< timeInfo->tm_hour % 12
    << ':' << std::setw(2) << std::setfill('0')<< timeInfo->tm_min
    << ':' << std::setw(2) << std::setfill('0')<< timeInfo->tm_sec
    << (timeInfo->tm_hour >= 12 ? " PM" : " AM");
    
    std::cout << std::setfill(' ');
}

void abs(int& a)
{
    if (a < 0)
        a = -a;
}


time_t tr::TimeRemainder::getnow() const
{
    return now;
}

tm tr::TimeRemainder::getTarget_time_tm() const
{
    return target_time_tm;
}

int tr::TimeRemainder::getDaysRemainder() const
{
    return daysRemainder;
}

int tr::TimeRemainder::getHoursRemainder() const
{
    return hoursRemainder;
}

int tr::TimeRemainder::getMinutesRemainder() const
{
    return minutesRemainder;
}

int tr::TimeRemainder::getSecondsRemainder() const
{
    return secondsRemainder;
}

std::string tr::TimeRemainder::toString() const
{
    return message;
}

void tr::TimeRemainder::printTimeDiffInfo() const
{
    int width = 3;
    std::cout << std::setw(width)<< this->message << ": "
    << std::setw(width) << abs(this->daysRemainder)<< " ds "
    << std::setw(width) <<abs(this->hoursRemainder) << " hs "
    << std::setw(width) <<abs(this->minutesRemainder) << " ms "
    << std::setw(width) <<abs(this->secondsRemainder) << " ss" << std::endl;
    
}

std::ostream& operator<< (std::ostream
                          & print, const tr::TimeRemainder& _tr)
{
    
    print << _tr.toString() << ": "
    << abs(_tr.getDaysRemainder())<< " days "
    << abs(_tr.getHoursRemainder()) << " hours "
    << abs(_tr.getMinutesRemainder()) << " minutes "
    << abs(_tr.getSecondsRemainder()) << " seconds" << std::endl;
    return print;
}
