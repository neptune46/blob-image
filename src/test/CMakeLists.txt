
cmake_minimum_required(VERSION 2.8)

# scale_image project
project(ffscale)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-D__STDC_CONSTANT_MACROS)

include_directories (ffscale ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/include)
link_directories(ffscale ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lib)
set (FFMPEG_LIBS avutil swscale)

add_executable(ffscale ff_scale_image.cpp)
target_link_libraries(ffscale ${FFMPEG_LIBS})

# blob_image project
project(cvblob)

include_directories (cvblob ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/include)
link_directories(cvblob ${CMAKE_CURRENT_SOURCE_DIR}/../../opencv/lib)
set (MY_OPENCV_LIBS opencv_world400d)

add_executable(cvblob cv_blob_image.cpp)
target_link_libraries( cvblob ${MY_OPENCV_LIBS} )
