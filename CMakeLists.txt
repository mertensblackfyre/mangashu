cmake_minimum_required(VERSION 3.10)
project(MangaShu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(spdlog REQUIRED)

add_executable(MangaShu
    main.cc
)

# Manually include libharu headers
target_include_directories(MangaShu PRIVATE
    /usr/include    # default path for libharu's hpdf.h on Arch
)

# Link to libhpdf manually
target_link_libraries(MangaShu PRIVATE
    hpdf
    spdlog::spdlog
)
