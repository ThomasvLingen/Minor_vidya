cmake_minimum_required(VERSION 3.6)
project(Minor_vidya)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cpp
        src/SDLFacade.hpp
	src/Raycasting.cpp src/Raycasting.hpp
		src/RayCastingTypes.hpp)

add_executable(Minor_vidya ${SOURCE_FILES})