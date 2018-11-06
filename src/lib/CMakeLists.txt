cmake_minimum_required(VERSION 3.0)

# scale_image project
project(libswblob)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-D__STDC_CONSTANT_MACROS)

include_directories (libswblob ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)
link_directories(libswblob ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
set (FFMPEG_LIBS avutil swscale avcodec avformat)

add_library(libswblob SHARED swblob.cpp swblob.h ffdec.cpp ffdec.h)
target_link_libraries(libswblob ${FFMPEG_LIBS})

include(GenerateExportHeader)
generate_export_header(libswblob)

add_custom_command(TARGET libswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/avutil-56.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/lib/Debug/avutil-56.dll")

add_custom_command(TARGET libswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/swscale-5.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/lib/Debug/swscale-5.dll")