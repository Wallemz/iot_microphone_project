add_library(recorder_lib)

target_sources(recorder_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src/microphone.cpp
        ${CMAKE_SOURCE_DIR}/src/microsd.cpp
        ${CMAKE_SOURCE_DIR}/src/recorder.cpp
)

target_include_directories(recorder_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(recorder_lib PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm hardware_adc hardware_dma hardware_rtc)