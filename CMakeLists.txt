cmake_minimum_required(VERSION 3.15)

project(IndieStudio)

set(CMAKE_C_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include(fetch_raylib.cmake)

include_directories(Include)
include_directories(Include/Encapsulation)
include_directories(Include/Menu)
include_directories(Include/Object)
include_directories(Include/Object/NotDisplayable)
include_directories(Include/Object/Displayable)
include_directories(Include/Object/Displayable/Movable)
include_directories(Include/Object/Displayable/Movable/Model3D)
include_directories(Include/Object/Displayable/Movable/Model3D/Player)
include_directories(Include/Object/Displayable/Static)
include_directories(Include/Object/Displayable/Static/UI)

add_executable(IndieStudio
                src/main.cpp
                src/Menu/End.cpp
                src/Menu/Splash_Screen.cpp
                src/Menu/Menu_Interface.cpp
                src/Menu/Menu_Setting.cpp
                src/Menu/Menu_Pause.cpp
                src/Menu/Menu_Personalisation.cpp
                src/GameMaster/Game_Master.cpp
                src/GameMaster/gm_inGame.cpp
                src/GameMaster/gm_drawInGame.cpp

                src/Object/Object.cpp
                src/Object/Displayable/Displayable.cpp
                src/Object/Displayable/Movable/Movable.cpp
                src/Object/Displayable/Movable/Model3D/Model3D.cpp
                src/Object/Displayable/Movable/Model3D/Player/Player.cpp
                src/Object/Displayable/Movable/Model3D/Player/playerMouv.cpp
                src/Object/Displayable/Movable/Model3D/Player/playerAttack.cpp
                src/Object/Displayable/Movable/Model3D/Map.cpp
                src/Object/Displayable/Movable/Model3D/Bonus.cpp
                src/Object/Displayable/Static/Static.cpp
                src/Object/Displayable/Static/UI/Button.cpp
                src/Object/Displayable/Static/UI/Slider.cpp
                src/Object/NotDisplayable/NotDisplayable.cpp
                src/Object/NotDisplayable/Camera.cpp)

target_link_libraries(${PROJECT_NAME} raylib)