add_executable(remote
    remote.cpp
    ImageData.c
    )

include_directories(../../lib/display/Config)
include_directories(../../lib/display/OLED)
include_directories(../../lib/display/GUI)
include_directories(../../lib/display/Fonts)
include_directories(../../lib/LoRa)

target_include_directories(remote PUBLIC ../../lib/display/Config)
target_include_directories(remote PUBLIC ../../lib/display/OLED)
target_include_directories(remote PUBLIC ../../lib/display/GUI)
target_include_directories(remote PUBLIC ../../lib/display/Fonts)
target_include_directories(remote PUBLIC ../../lib/LoRa)

target_link_directories(remote PUBLIC ../../lib/display/Config)
target_link_directories(remote PUBLIC ../../lib/display/OLED)
target_link_directories(remote PUBLIC ../../lib/display/GUI)
target_link_directories(remote PUBLIC ../../lib/display/Fonts)
target_link_directories(remote PUBLIC ../../lib/LoRa)


target_link_libraries(remote
    pico_stdlib
    hardware_spi
    LoRa_pico_lib
    Config
    GUI
    Fonts
    OLED
)

pico_enable_stdio_uart(remote 0)
pico_enable_stdio_usb(remote 1)
pico_add_extra_outputs(remote)