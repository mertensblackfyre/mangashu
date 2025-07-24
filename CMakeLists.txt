cmake_minimum_required(VERSION 3.10)
project(MangaShu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(spdlog REQUIRED)
find_package(qpdf REQUIRED)

add_executable(MangaShu
    main.cc
)

target_include_directories(MangaShu PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    /usr/include   # for libharu headers on Arch
)

# Link to libraries
target_link_libraries(MangaShu PRIVATE
    hpdf
     qpdf::libqpdf
    spdlog::spdlog
)
