#ifndef EFFICIENT_LOGGING_SYSTEM_ASYNC_LOGGER_H
#define EFFICIENT_LOGGING_SYSTEM_ASYNC_LOGGER_H

#include <mutex>
#include <iostream>
#include <string>
#include <cstdint>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <thread>
class async_logger {
private:
    std::mutex mtx;
    std::queue<std::string_view> msg_queue;
    std::condition_variable cond;
    std::ofstream out_file;
    bool is_quit;
public:
    async_logger();
    ~async_logger();
    void write_one(const std::string_view & msg);
    void run(); //用lambda挂起一个异步线程
    void quit();
};


#endif //EFFICIENT_LOGGING_SYSTEM_ASYNC_LOGGER_H
