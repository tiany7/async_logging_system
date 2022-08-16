#include <iostream>
#include "async_logger.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    async_logger logger;
    logger.run();
    logger.write_one("dd");


    getchar();
    logger.quit();
    logger.wait();
    return 0;
}
