cmake_minimum_required(VERSION 3.20)
project(efficient_logging_system)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D WIN_DEBUG)
add_executable(efficient_logging_system main.cpp async_logger.cpp async_logger.h)
