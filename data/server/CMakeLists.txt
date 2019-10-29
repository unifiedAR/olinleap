cmake_minimum_required(VERSION 3.14)
project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/)
find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

set(SOURCE_FILES main.cpp)
add_executable(server ${SOURCE_FILES})

target_include_directories(server PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(server PUBLIC ${ZeroMQ_LIBRARY})