add_executable(house house.cpp)

include_directories(../../lib/LoRa)

target_include_directories(house PUBLIC ../../lib/LoRA)
target_link_directories(house PUBLIC ../../lib/LoRa)

target_link_libraries(house pico_stdlib LoRa_pico_lib hardware_gpio)

pico_enable_stdio_uart(house 0)
pico_enable_stdio_usb(house 1)

pico_add_extra_outputs(house)