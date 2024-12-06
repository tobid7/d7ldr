cmake_minimum_required(VERSION 3.18)

# Setup Toolchain if not specified
# Could propably avoided by using arm-none-eabi-cmake
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{DEVKITPRO})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{DEVKITPRO}/cmake/3DS.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define DEVKITPRO to point to your SDK path!")
    endif()
endif()

# Set Result specific Data
set(APP_NAME "d7ldr_cpp_test")
set(APP_DESC "C++ Test of D7LDR lib")
set(APP_AUTHOR "tobid7")

# Set 3ds IP for make send
set(3DS_IP "192.168.2.224" CACHE STRING "3ds IP (make send)")

# Set Project
project(d7ldr_cpp_test LANGUAGES C CXX VERSION 1.0.0)

# Enable Compile Command Export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set Special C and CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-psabi -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions")

# Set Executable and its sources
add_executable(d7ldr_cpp_test
    source/main.cpp
)

# Set dependencies, include dirs and definitions
target_link_libraries(d7ldr_cpp_test PUBLIC m d7ldr ctru)
target_include_directories(d7ldr_cpp_test PUBLIC
    ${DEVKITPRO}/portlibs/3ds/include
)
target_compile_definitions(d7ldr_cpp_test PUBLIC
    -D_GNU_SOURCE=1
)

# Command to send to console (make send)
add_custom_target(
    send
    COMMAND 3dslink -a "${3DS_IP}" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.3dsx"
)

# Generate 3DSX
ctr_create_3dsx(
    d7ldr_cpp_test
    OUTPUT "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.3dsx"
    NOSMDH
)