//
// Created by tiany on 2022/8/16.
//

#ifndef EFFICIENT_LOGGING_SYSTEM_UTIL_H
#define EFFICIENT_LOGGING_SYSTEM_UTIL_H
#include <string>
#include <ctime>
#include "environment.h"
std::string GetLogFileName(){
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);
    std::string iFileName = std::to_string(1900 + p->tm_year) + (std::to_string(1+ p->tm_mon).length() > 1 ? std::to_string(1+ p->tm_mon) : "0" + std::to_string(1+ p->tm_mon));
    iFileName += ((std::to_string((p->tm_mday)).length() > 1) ?  std::to_string(p->tm_mday) : ("0" + std::to_string(p->tm_mday)));
    iFileName += ((std::to_string((p->tm_hour - 2 - 3 + 24) % 24).length() > 1) ?  std::to_string((p->tm_hour - 2 - 3 + 24) % 24) : ("0" + std::to_string((p->tm_hour - 2 - 3 + 24) % 24)));
    return env::name + iFileName + ".log";
};

std::string GetTimeMs(){
    std::string defaultTime = "19700101000000000";
    try
    {
#if  defined(__linux__)
        struct timeval curTime;
        gettimeofday(&curTime, NULL);
        int milli = curTime.tv_usec / 1000;

        char buffer[80] = {0};
        struct tm nowTime;
        localtime_r(&curTime.tv_sec, &nowTime);//把得到的值存入临时分配的内存中，线程安全
        nowTime.tm_hour += 24 - 5;
        nowTime.tm_hour %= 24; // 做时区转换用
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S:", &nowTime);

        char currentTime[84] = {0};
        snprintf(currentTime, sizeof(currentTime), "%s%03d", buffer, milli);

        return currentTime;
#else
        time_t nowTime = time(NULL);
        struct tm *t = localtime(&nowTime);
        char buffer[30];
        sprintf(buffer, "%d-%d-%d %d:%d:%d", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        return buffer;

#endif
    }
    catch(const std::exception& e)
    {
        return defaultTime;
    }
    catch (...)
    {
        return defaultTime;
    }

};
#endif //EFFICIENT_LOGGING_SYSTEM_UTIL_H
