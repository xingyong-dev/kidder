cmake_minimum_required(VERSION 3.24)
project(kidder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(spdlog REQUIRED)

add_subdirectory(src/signal)
add_executable(kidder app/signaltiming.cpp)

target_link_libraries(kidder PRIVATE signal_handler)