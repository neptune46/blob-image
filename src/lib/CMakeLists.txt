cmake_minimum_required(VERSION 3.0)

# scale_image project
project(swblob)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-D__STDC_CONSTANT_MACROS)

include_directories (swblob ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)

if (WIN32)
    link_directories(swblob ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
endif (WIN32)
if (UNIX)
    link_directories(swblob ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/linux)
endif (UNIX)

set (FFMPEG_LIBS avutil swscale avcodec avformat)

add_library(swblob SHARED swblob.cpp swblob.h ffdec.cpp ffdec.h image.cpp image.h)
target_link_libraries(swblob ${FFMPEG_LIBS})

include(GenerateExportHeader)
generate_export_header(swblob)
