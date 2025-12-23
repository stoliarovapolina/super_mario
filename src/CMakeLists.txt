cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(os_controls)
add_subdirectory(controller)
add_subdirectory(levels)
add_subdirectory(model)
add_subdirectory(objects)
add_subdirectory(ui)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/model"
	"${CMAKE_CURRENT_SOURCE_DIR}/objects"
	"${CMAKE_CURRENT_SOURCE_DIR}/controller"
	"${CMAKE_CURRENT_SOURCE_DIR}/levels"
	"${CMAKE_CURRENT_SOURCE_DIR}/ui"
	"${CMAKE_CURRENT_SOURCE_DIR}/ui/console"
	"${CMAKE_CURRENT_SOURCE_DIR}/ui/console/ui_objects"
)