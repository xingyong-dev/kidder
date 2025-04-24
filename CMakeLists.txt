cmake_minimum_required(VERSION 3.24)
project(kidder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.13.0  # 推荐使用具体版本
)

FetchContent_MakeAvailable(spdlog)

add_subdirectory(src/signal)

add_executable(kidder app/signaltiming.cpp)

target_link_libraries(kidder PRIVATE signal_handler spdlog::spdlog)