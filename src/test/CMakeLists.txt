
cmake_minimum_required(VERSION 2.8)

# ffscale test app
project(ffscale)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-D__STDC_CONSTANT_MACROS)

include_directories (ffscale ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)
link_directories(ffscale ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
set (FFMPEG_LIBS avutil swscale)

add_executable(ffscale test_ff_scale.cpp)
target_link_libraries(ffscale ${FFMPEG_LIBS})

# cvblob test app
project(cvblob)

include_directories (cvblob ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/include)
link_directories(cvblob ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/lib)
set (MY_OPENCV_LIBS opencv_world400d)

add_executable(cvblob test_cv_blob.cpp)
target_link_libraries( cvblob ${MY_OPENCV_LIBS} )

# swblob test app
project(testswblob)

include_directories (testswblob 
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/include)

link_directories(testswblob 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/lib/Debug
    ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/lib)

set (MY_OPENCV_LIBS opencv_world400d)

add_executable(testswblob test_swblob.cpp)
target_link_libraries(testswblob libswblob ${MY_OPENCV_LIBS})