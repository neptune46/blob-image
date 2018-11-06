cmake_minimum_required(VERSION 3.0)

# swblob test app
project(testswblob)

set (CMAKE_CXX_STANDARD 11)

include_directories (testswblob 
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)

link_directories(testswblob 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/lib/Debug
    ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)

add_executable(testswblob test_swblob.cpp perf_util.h perf_util.cpp)
target_link_libraries(testswblob libswblob opencv_world400d)

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/lib/Debug/libswblob.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/libswblob.dll")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/avutil-56.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/avutil-56.dll")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/swscale-5.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/swscale-5.dll")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/avcodec-58.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/avcodec-58.dll")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/avformat-58.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/avformat-58.dll")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/bin/swresample-3.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/swresample-3.dll")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../data/test_rgb24_300x300.rgb"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/test_rgb24_300x300.rgb")

add_custom_command(TARGET testswblob POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../data/test_yuyv_640x480.yuv"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/test/Debug/test_yuyv_640x480.yuv")