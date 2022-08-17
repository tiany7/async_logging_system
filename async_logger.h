#ifndef EFFICIENT_LOGGING_SYSTEM_ASYNC_LOGGER_H
#define EFFICIENT_LOGGING_SYSTEM_ASYNC_LOGGER_H
#ifdef _WIN32
#include <io.h>
#define access    _access_s
#else
#include <unistd.h>
#endif
#include <mutex>
#include <iostream>
#include <string>
#include <cstdint>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <thread>
#include <future>

class async_logger {
private:
    std::mutex mtx;
    std::queue<std::string_view> msg_queue;
    std::condition_variable cond;
    std::ofstream out_file;
    bool is_quit = false;
    bool exited = false;
public:
    async_logger();
    ~async_logger();
    void write_one(const std::string_view & msg);
    void run(); //用lambda挂起一个异步线程
    void Stop();
    void wait();
};


#endif //EFFICIENT_LOGGING_SYSTEM_ASYNC_LOGGER_H
