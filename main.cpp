#include <iostream>
#include "fastlog.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    async_logger logger;
    logger.run();
    XLOG(logger, "yes", 23333);
    return 0;
}
