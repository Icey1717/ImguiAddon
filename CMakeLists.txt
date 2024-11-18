cmake_minimum_required(VERSION 3.14)
project(ImguiAddOnImpl VERSION 1.0 LANGUAGES CXX)

add_subdirectory(ImguiAddOn)

add_executable(ImguiAddOnImpl src/main.cpp)

target_link_libraries(ImguiAddOnImpl PRIVATE ImguiAddOn)