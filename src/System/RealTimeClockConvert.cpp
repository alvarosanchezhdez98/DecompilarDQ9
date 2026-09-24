#include "System/RealTimeClock.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's rtc_convert.c: converts dates and times to days and seconds since January 1, 2000, and back

// The days before each month in a year that isn't a leap year
static long daysBeforeMonth[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

// RTCi_IsLeapYear: every 4 years, from 2000 to 2099. An inline function in C, whose ! gives an int: in C++, it would
// give a bool, which the compiler turns into 0 or 1.
#define IsLeapYear(year) (!((year) & 3))

extern "C"
{
    // usa: func_020cf8e4
    // RTC_ConvertDateToDay
    long func_020cf8e4(const RealTimeClockDate* date)
    {
        long day;

        if (date->year >= 100 || date->month < 1 || date->month > 12 || date->day < 1 || date->day > 31 ||
            date->dayOfWeek >= 7 || date->month < 1 || date->month > 12)
        {
            return -1;
        }

        day = (long)(date->day - 1);
        day += daysBeforeMonth[date->month - 1];
        if (date->month >= 3 && IsLeapYear(date->year))
        {
            day++;
        }
        day += date->year * 365;
        day += (date->year + 3) / 4;
        return day;
    }

    // usa: func_020cf978
    // RTCi_ConvertTimeToSecond
    long func_020cf978(const RealTimeClockTime* time)
    {
        return (long)((time->hour * 60 + time->minute) * 60 + time->second);
    }

    // usa: func_020cf990
    // RTC_ConvertDateTimeToSecond
    long long func_020cf990(const RealTimeClockDate* date, const RealTimeClockTime* time)
    {
        long day, second;

        day = func_020cf8e4(date);
        if (day == -1)
        {
            return -1;
        }
        second = func_020cf978(time);
        if (second == -1)
        {
            return -1;
        }
        return (long long)day * (60 * 60 * 24) + second;
    }

    // usa: func_020cf9f4
    // RTC_ConvertDayToDate
    void func_020cf9f4(RealTimeClockDate* date, long day)
    {
        unsigned long year;
        long month;

        if (day < 0)
        {
            day = 0;
        }
        if (day > 36524)
        {
            day = 36524;
        }

        // January 1, 2000 was a Saturday
        date->dayOfWeek = (day + 6) % 7;

        for (year = 0; year < 99; year++)
        {
            long previous = day;
            day -= IsLeapYear(year) ? 366 : 365;
            if (day < 0)
            {
                day = previous;
                break;
            }
        }
        if (day > 365)
        {
            day = 365;
        }
        date->year = year;

        if (IsLeapYear(year))
        {
            if (day < 31 + 29)
            {
                if (day < 31)
                {
                    month = 1;
                }
                else
                {
                    month = 2;
                    day -= 31;
                }
                date->month = (unsigned long)month;
                date->day = (unsigned long)(day + 1);
                return;
            }
            else
            {
                day--;
            }
        }

        for (month = 11; month >= 0; month--)
        {
            if (day >= daysBeforeMonth[month])
            {
                date->month = (unsigned long)(month + 1);
                date->day = (unsigned long)(day - daysBeforeMonth[month] + 1);
                return;
            }
        }
    }

    // usa: func_020cfaf4
    // RTCi_ConvertSecondToTime
    void func_020cfaf4(RealTimeClockTime* time, long second)
    {
        if (second < 0)
        {
            second = 0;
        }
        if (second > 86399)
        {
            second = 86399;
        }

        time->second = (unsigned long)(second % 60);
        second /= 60;
        time->minute = (unsigned long)(second % 60);
        second /= 60;
        time->hour = (unsigned long)second;
    }

    // usa: func_020cfb74
    // RTC_ConvertSecondToDateTime
    void func_020cfb74(RealTimeClockDate* date, RealTimeClockTime* time, long long second)
    {
        if (second < 0)
        {
            second = 0;
        }
        else if (second > 3155759999)
        {
            second = 3155759999;
        }
        func_020cfaf4(time, (long)(second % 86400));
        func_020cf9f4(date, (long)(second / 86400));
    }

    // usa: func_020cfc00
    // RTC_GetDayOfWeek
    int func_020cfc00(RealTimeClockDate* date)
    {
        int century;
        int year = (int)(2000 + date->year);
        int month = (int)date->month;
        int day = (int)date->day;

        // Zeller's congruence, with the year starting in March
        month -= 2;
        if (month < 1)
        {
            month += 12;
            --year;
        }
        century = year / 100;
        year %= 100;
        return (int)(((26 * month - 2) / 10 + day + year + year / 4 + century / 4 + 5 * century) % 7);
    }
}
