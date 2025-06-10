cmake_minimum_required(VERSION 3.12)
project(MangaShu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAGICKCORE_QUANTUM_DEPTH 16)  # Must match your installed version (Q16)
set(MAGICKCORE_HDRI_ENABLE 0)     # Must match your installed version (0 for non-HDRI)

find_package(ImageMagick COMPONENTS Magick++ MagickWand MagickCore REQUIRED)

find_package(spdlog REQUIRED)

add_executable(MangaShu
   main.cc
)

target_compile_definitions(MangaShu PRIVATE
    MAGICKCORE_QUANTUM_DEPTH=${MAGICKCORE_QUANTUM_DEPTH}
    MAGICKCORE_HDRI_ENABLE=${MAGICKCORE_HDRI_ENABLE}
)

target_include_directories(MangaShu PRIVATE
    ${ImageMagick_INCLUDE_DIRS}
)

target_link_libraries(MangaShu PRIVATE
    ${ImageMagick_LIBRARIES}
    spdlog::spdlog
)

target_link_libraries(MangaShu PRIVATE
    Magick++
    MagickWand
    MagickCore
)
