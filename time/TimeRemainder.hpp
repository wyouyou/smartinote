//
//  TimeRemainder.hpp
//  当前时间-计时器
//
//  Created by Jaye Wang on 8/8/17.
//  Copyright © 2017 JayeWang. All rights reserved.
//

#ifndef TimeRemainder_hpp
#define TimeRemainder_hpp

#include <iostream>
#include <iomanip>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */


//using namespace std;

namespace tr {
    class TimeRemainder;
}

/********************************************************************/
//struct tm {
//    int tm_sec;         /* seconds,  range 0 to 59          */
//    int tm_min;         /* minutes, range 0 to 59           */
//    int tm_hour;        /* hours, range 0 to 23             */
//    int tm_mday;        /* day of the month, range 1 to 31  */
//    int tm_mon;         /* month, range 0 to 11             */
//    int tm_year;        /* The number of years since 1900   */
//    int tm_wday;        /* day of the week, range 0 to 6    */
//    int tm_yday;        /* day in the year, range 0 to 365  */
//    int tm_isdst;       /* daylight saving time             */

//The Daylight Saving Time flag (tm_isdst) is greater than zero if Daylight Saving Time is in effect, zero if Daylight Saving Time is not in effect, and less than zero if the information is not available.
//};


/********************************************************************/

/**
 * now is an number of seconds since 00:00 hours, Jan 1, 1970 UTC( UTC 是Coordinated Universal Time 的缩写，译为中文为“世界标准时间”)
 * target_time_time_t is the time of arg passed from client, a struct with user-orgranizde time relelated member.
 * target_time_time_t is the time of arg passed from client, an number of seconds.
 * daysRemainder is the number of day difference between now to the time represented by the arg passed from the client.
 * hoursRemainder is the number of hour difference...
 * ....
 * message is the prompt to be printed before the time difference message   
 * displayed on screen.
 
 * Data member are all positve if the target time is not comming yet, negative otherwise.
 * Note the abs() member function could get rid of the minus sign if needed.
 */
class tr::TimeRemainder{
    
protected:
    time_t now;
    tm target_time_tm;
    time_t target_time_time_t;
    int daysRemainder;
    int hoursRemainder;
    int minutesRemainder;  
    int secondsRemainder;
    std::string message;
    
public:
    static const int SECONDS_PER_DAY = 24 * 60 * 60;
    static const int SECONDS_PER_HOUR = 60 * 60;
    static const int SECOND_PER_MINUTE = 60;

    /**
     *Ex: construct the time difference from now until 12/25/2017/12/12/12
     *
     * Call like this: TimeRemainder(9,25,2017,0,0,0,1);
     
     */
    TimeRemainder(const int& month, const int& day_of_month,
                  const int& year,  const int& hour,
                  const int& minutes, const int & seconds,
                  const int& isDaySavingTime,
                  const std::string& message
                  );
    
    /**
     * Print the current time
     */
    void printCurrentTime() const;
    
    void printTimeDiffInfo() const;

    
    
    /**
     * Accessor functions
     */
    time_t getnow() const;
    tm getTarget_time_tm() const;
    int getDaysRemainder() const;
    int getHoursRemainder() const;
    int getMinutesRemainder() const;
    int getSecondsRemainder() const;
    std::string toString() const;
    
    
};

/**
 * Overloaded stream insertion operator << to print a TimeRemainder.
 */
std::ostream& operator<<(std::ostream&,const tr::TimeRemainder&);



#endif /* TimeRemainder_hpp */
