cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(pico_microphone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_subdirectory(lib/microphone)
add_subdirectory(lib/microsd)
include_directories(./lib/microphone)
include_directories(./lib/microsd)


add_executable(main 
    main.cpp
)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)

target_link_libraries(main 
    microphone 
    microsd
    pico_stdlib 
    hardware_adc)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )