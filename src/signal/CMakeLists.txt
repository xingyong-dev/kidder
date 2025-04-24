add_library(signal_handler STATIC SignalHandler.cpp)
target_include_directories(signal_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(signal_handler PUBLIC spdlog::spdlog)
target_compile_features(signal_handler PUBLIC cxx_std_17)