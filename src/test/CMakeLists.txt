
cmake_minimum_required(VERSION 2.8)

project(scaleimg)
project(blobimg)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-D__STDC_CONSTANT_MACROS)

# scale_image project

include_directories (scaleimg ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)
link_directories(scaleimg ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
set (FFMPEG_LIBS avutil swscale)

add_executable(scaleimg scale_image.cpp)
target_link_libraries(scaleimg ${FFMPEG_LIBS})

# blob_image project

include_directories (blobimg ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)
link_directories(blobimg ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
set (FFMPEG_LIBS opencv_world400d)

add_executable(blobimg blob_image.cpp)
target_link_libraries( blobimg ${OpenCV_LIBS} )
