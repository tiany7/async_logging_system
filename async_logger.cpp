

#include "async_logger.h"

async_logger::async_logger() : is_quit(false){

}

async_logger::~async_logger() {
    while(!msg_queue.empty()){
        msg_queue.pop();
    }
}

void async_logger::write_one(const std::string_view &msg) {
    msg_queue.push(msg);
    cond.notify_one();
}

void async_logger::run() {
    auto runner = std::thread([this](){
        while(!is_quit){
            std::unique_lock<std::mutex> lck;
            cond.wait(lck, [this]()->bool{
                return msg_queue.empty();
            });

        }
    });
    runner.
}
