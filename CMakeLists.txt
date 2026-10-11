cmake_minimum_required(VERSION 3.10)

project(MercuryBoot)

add_subdirectory(lib/MercuryCAN)

add_executable(MercuryBoot src/main.cpp)

target_link_libraries(MercuryBoot PRIVATE MercuryCAN)