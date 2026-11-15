# rpi5cpc: the Amstrad CPC 464, 664, 6128, 464 Plus and 6128 Plus on the
# Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5cpc --help
#
# The CPC itself is esp32cpc's (../esp32cpc/components/cpc, platform
# independent), the runtime rpi5emu's (../rpi5emu), the Z80 and the uPD765
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5cpc C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32CPC_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32cpc" CACHE PATH "esp32cpc checkout: the CPC")
if(NOT EXISTS "${ESP32CPC_DIR}/components/cpc/include/cpc.h")
    message(FATAL_ERROR "No esp32cpc at ${ESP32CPC_DIR}: clone github.com/rlucencic/esp32cpc beside rpi5cpc")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB CPC_SOURCES "${ESP32CPC_DIR}/components/cpc/*.c")
add_executable(rpi5cpc
    src/main.c
    src/settings.c
    src/rom_store.c
    ${CPC_SOURCES})
target_include_directories(rpi5cpc PRIVATE
    src
    "${ESP32CPC_DIR}/components/cpc/include"
    "${ESP32CPC_DIR}/components/cpc")
# The Z80 in the CPC's microseconds (the Gate Array's), as esp32cpc's
target_compile_definitions(rpi5cpc PRIVATE CONFIG_Z80_TIMING_CPC=1)
rpi5emu_add_cores(rpi5cpc z80 upd765 diskspace)
target_link_libraries(rpi5cpc PRIVATE rpi5emu)
target_compile_options(rpi5cpc PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS rpi5cpc)
