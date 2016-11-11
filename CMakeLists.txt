cmake_minimum_required(VERSION 3.6)
project(Minor_vidya)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    	src/main.cpp
		src/SDLFacade.hpp src/SDLFacade.cpp
		src/Raycasting.cpp src/Raycasting.hpp
		src/RayCastingTypes.hpp
		src/Color.hpp
		src/CoordinateDouble.hpp
		src/PointOfView.hpp src/PointOfView.cpp
		src/RaycastingVector.hpp
		src/TileObject.hpp src/TileObject.cpp
		src/WorldObject.hpp
		src/Game.cpp src/Game.hpp
)

add_executable(Minor_vidya ${SOURCE_FILES})