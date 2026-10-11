cmake_minimum_required(VERSION 3.10)

project(MercuryBoot)

add_subdirectory(lib/MercuryCAN)

add_executable(
    MercuryBoot 
    src/main.cpp 
    src/memory/flash.cpp 
    src/memory/eeprom.cpp 
    src/memory/sram.cpp   
)

target_link_libraries(MercuryBoot PRIVATE MercuryCAN)
target_include_directories(MercuryBoot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)