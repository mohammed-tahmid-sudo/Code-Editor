# cmake_minimum_required(VERSION 3.16)
# project(CodeEditor LANGUAGES CXX)
#
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
#
# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
#
# file(GLOB SRC_FILES src/*.cpp)
#
# add_executable(${PROJECT_NAME} ${SRC_FILES})
#
# target_link_libraries(${PROJECT_NAME}
#     Qt6::Core
#     Qt6::Gui
#     Qt6::Widgets
# )


cmake_minimum_required(VERSION 3.16)
project(CodeEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(QScintilla2 REQUIRED)

file(GLOB SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# make run target
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

