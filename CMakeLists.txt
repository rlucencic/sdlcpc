# sdlcpc: the Amstrad CPC 464, 664, 6128, 464 Plus and 6128 Plus with
# SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlcpc --help
#
# The CPC itself is esp32cpc's (../esp32cpc/components/cpc, platform
# independent), the runtime sdlemu's (../sdlemu), the Z80 and the uPD765
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlcpc C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32CPC_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32cpc" CACHE PATH "esp32cpc checkout: the CPC")
if(NOT EXISTS "${ESP32CPC_DIR}/components/cpc/include/cpc.h")
    message(FATAL_ERROR "No esp32cpc at ${ESP32CPC_DIR}: clone github.com/rlucencic/esp32cpc beside sdlcpc")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

file(GLOB CPC_SOURCES "${ESP32CPC_DIR}/components/cpc/*.c")
add_executable(sdlcpc
    src/main.c
    src/settings.c
    src/rom_store.c
    ${CPC_SOURCES})
target_include_directories(sdlcpc PRIVATE
    src
    "${ESP32CPC_DIR}/components/cpc/include"
    "${ESP32CPC_DIR}/components/cpc")
# The Z80 in the CPC's microseconds (the Gate Array's), as esp32cpc's
target_compile_definitions(sdlcpc PRIVATE CONFIG_Z80_TIMING_CPC=1)
sdlemu_add_cores(sdlcpc z80 upd765 diskspace)
target_link_libraries(sdlcpc PRIVATE sdlemu)
target_compile_options(sdlcpc PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS sdlcpc)
