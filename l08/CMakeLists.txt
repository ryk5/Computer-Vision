cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
add_executable( l082 l082.cpp )
target_link_libraries( l082 ${OpenCV_LIBS} )

