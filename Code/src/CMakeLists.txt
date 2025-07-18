cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(chicken-house C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_subdirectory(src)
add_subdirectory(lib/display/Config)
add_subdirectory(lib/display/OLED)
add_subdirectory(lib/display/Fonts)
add_subdirectory(lib/display/GUI)
add_subdirectory(lib/LoRa)

include_directories(lib/display/Config)
include_directories(lib/display/OLED)
include_directories(lib/display/Fonts)
include_directories(lib/display/GUI)
include_directories(lib/LoRa)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()