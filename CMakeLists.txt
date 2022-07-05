cmake_minimum_required(VERSION 3.22)
project(advisorbot)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(advisorbot
        AdvisorMain.cpp
        AdvisorMain.h
        main.cpp Order.cpp Order.h OrderBook.cpp OrderBook.h Helpers.cpp Helpers.h Math.cpp Math.h)
