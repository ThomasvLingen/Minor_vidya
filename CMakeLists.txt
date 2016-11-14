cmake_minimum_required(VERSION 3.6)
project(Minor_vidya)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    	src/main.cpp
		src/engine/SDLFacade.hpp src/engine/SDLFacade.cpp
		src/engine/raycasting/Raycasting.cpp src/engine/raycasting/Raycasting.hpp
		src/engine/raycasting/RayCastingTypes.hpp
		src/engine/domain/Color.hpp src/engine/domain/Color.cpp
		src/engine/domain/CoordinateDouble.hpp
		src/gamelogic/Level.cpp src/gamelogic/Level.hpp
		src/engine/domain/PointOfView.hpp src/engine/domain/PointOfView.cpp
		src/engine/raycasting/RaycastingVector.hpp
		src/engine/domain/TileObject.hpp src/engine/domain/TileObject.cpp
		src/engine/domain/WorldObject.hpp
		src/gamelogic/Game.cpp src/gamelogic/Game.hpp
		src/gamelogic/Player.cpp src/gamelogic/Player.hpp

)

add_executable(Minor_vidya ${SOURCE_FILES})