cmake_minimum_required(VERSION 3.1.0)
project(beam_fight)

add_executable(${PROJECT_NAME} 
	code/beamfight.cpp
	code/globalsettings.cpp
	code/player.cpp
	code/pocisk.cpp
	code/pociskmanager.cpp
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/settings.txt
            ${CMAKE_CURRENT_BINARY_DIR}/Debug/
)