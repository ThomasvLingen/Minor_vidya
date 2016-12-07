cmake_minimum_required(VERSION 3.6)
project(Minor_vidya)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
		"src/*.cpp"
		"src/*.hpp"
		)

add_executable(Minor_vidya ${SOURCE_FILES})