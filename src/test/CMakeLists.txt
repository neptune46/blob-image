cmake_minimum_required(VERSION 3.0)

# swblob test app
project(testswblob)

set (CMAKE_CXX_STANDARD 11)

include_directories (testswblob 
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)

if (WIN32)
    set(OPENCV_LIB opencv_world400d)
    set(SWBLOB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/lib/Debug)
endif (WIN32)
if (UNIX)
    set(OPENCV_LIB opencv_world)
    set(SWBLOB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../build/linux/lib/Debug)
endif (UNIX)

link_directories(testswblob 
    ${SWBLOB_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)

add_executable(testswblob test_swblob.cpp)
target_link_libraries(testswblob swblob ${OPENCV_LIB})
