project(Project)
cmake_minimum_required(VERSION 2.8)
set(wxWidgets_ROOT_DIR </home/englesson/Programming/wxWidgets>)
aux_source_directory(. SRC_LIST)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SRC_LIST})
set( CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++11" )
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB SOURCES tests/*.cpp)
file(GLOB SOURCES tests/*.h)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

