

#include "async_logger.h"

async_logger::async_logger() : is_quit(false){

}

async_logger::~async_logger() {
    while(!msg_queue.empty()){
        msg_queue.pop();
    }
    if(out_file.is_open()){
        out_file.close();
    }
}

void async_logger::write_one(const std::string_view &msg) {
    msg_queue.push(msg);
    cond.notify_one();
}

//挂起一个线程
void async_logger::run() {
    auto runner = std::thread([this](){
        while(!is_quit){
            std::unique_lock<std::mutex> lck(mtx);
            cond.wait(lck, [this]()->bool{
                return !msg_queue.empty() or !is_quit;
            });

#if defined(__linux__)
            struct stat buf;
            if(stat(R"(C:\Users\tiany\CLionProjects\tiany7's Logging System\test.log)", &buf) == 0){
                out_file.open(R"(C:\Users\tiany\CLionProjects\tiany7's Logging System\test.log)", std::ios::app);
            }
#elif defined(__WIN32__)
            if(access(R"(C:\Users\tiany\CLionProjects\tiany7's Logging System\test.log)", 0) or !out_file.is_open()){
                out_file.open(R"(C:\Users\tiany\CLionProjects\tiany7's Logging System\test.log)", std::ios::app);
            }
#endif
            while(!msg_queue.empty()){
                out_file<<msg_queue.front()<<std::endl;
                msg_queue.pop();
            }
        }
        exited = true;
    });
    runner.detach();
}

void async_logger::wait() {
    while(!exited){
        std::this_thread::sleep_for(std::chrono::microseconds(2));
    }
}

void async_logger::Stop() {
    is_quit = true;
    cond.notify_one();
}