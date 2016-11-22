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
		src/engine/domain/WorldObject.cpp src/engine/domain/WorldObject.hpp
		src/gamelogic/Game.cpp src/gamelogic/Game.hpp
		src/gamelogic/Player.cpp src/gamelogic/Player.hpp
		src/gamelogic/VectorUtil.cpp src/gamelogic/VectorUtil.hpp
		src/gamelogic/Tile.cpp src/gamelogic/Tile.hpp
		src/engine/KeyStrokes.hpp
		src/config.hpp
		src/engine/interface/Drawable.cpp src/engine/interface/Drawable.hpp
		src/engine/interface/Updatable.hpp
		src/engine/FPScounter.cpp src/engine/FPScounter.hpp
		src/engine/interface/Handleable.hpp
		src/engine/interface/Collection.cpp src/engine/interface/Collection.hpp
		src/engine/AssetsManager.cpp src/engine/AssetsManager.hpp
		src/gamelogic/state/IGameState.hpp
		src/gamelogic/state/CreditState.cpp src/gamelogic/state/CreditState.hpp
		src/gamelogic/state/Menu.cpp src/gamelogic/state/Menu.hpp
		src/gamelogic/state/MenuOption.cpp src/gamelogic/state/MenuOption.hpp
		src/gamelogic/state/MenuState.cpp src/gamelogic/state/MenuState.hpp
		src/gamelogic/state/StartUpState.cpp src/gamelogic/state/StartUpState.hpp
		src/gamelogic/state/HelpState.cpp src/gamelogic/state/HelpState.hpp
		src/gamelogic/state/LoadState.cpp src/gamelogic/state/LoadState.hpp
		)

add_executable(Minor_vidya ${SOURCE_FILES})