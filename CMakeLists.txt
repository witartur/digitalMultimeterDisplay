cmake_minimum_required(VERSION 3.22.1)
project(voltageDisplay LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED On)
set(CMAKE_C_EXTENSIONS Off)

set(CMAKE_C_COMPILER clang)

add_library(
    src
    uptime.c
    digital_multimeter.c
    display.c
    support.c
)
add_executable(voltageDisplay main.c)
add_executable(unitTests test.c)

target_link_libraries(voltageDisplay PRIVATE src m)
target_link_libraries(unitTests PRIVATE src m)

add_custom_target(run COMMAND voltageDisplay DEPENDS voltageDisplay)
add_custom_target(test COMMAND unitTests DEPENDS unitTests)
