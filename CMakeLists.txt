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

# Get GIT Commit Hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_SHORT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Set Project
project(d7ldr LANGUAGES C CXX VERSION 1.0.0)

# Enable Compile Command Export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set Special C and CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-psabi -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions")

# Set Executable and its sources
add_library(d7ldr STATIC # Shared not possible btw
    source/rosalina.cpp
    source/d7ldr.cpp
)

# Set dependencies, include dirs and definitions
target_include_directories(d7ldr PUBLIC
    include
    ${DEVKITPRO}/portlibs/3ds/include
    ${DEVKITPRO}/libctru/include
)
target_compile_definitions(d7ldr PUBLIC
    -D_GNU_SOURCE=1
    -DD7LDR_VERSION="${PROJECT_VERSION}"
    -DD7LDR_GIT_COMMIT="${GIT_SHORT_HASH}"
    -DBUILD_D7LDR # Avoids the warning of the c wrapper
)

install(TARGETS d7ldr)
install(DIRECTORY include DESTINATION ".")