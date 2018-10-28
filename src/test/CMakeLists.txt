
cmake_minimum_required(VERSION 2.8)

project(scaleimg)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-D__STDC_CONSTANT_MACROS)

include_directories (scaleimg ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)
link_directories(scaleimg ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
set (FFMPEG_LIBS avutil swscale)

add_executable(scaleimg scale_image.cpp)
target_link_libraries(scaleimg ${FFMPEG_LIBS})
