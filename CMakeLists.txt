cmake_minimum_required(VERSION 3.16)
project(CodeEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure folder structure
file(MAKE_DIRECTORY
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/resources/themes
)

# Create minimal files if not present
set(MAIN_CPP ${CMAKE_SOURCE_DIR}/src/main.cpp)
if(NOT EXISTS ${MAIN_CPP})
    file(WRITE ${MAIN_CPP} "#include <QApplication>\n#include <QMainWindow>\n#include <QPlainTextEdit>\n\nint main(int argc, char *argv[]) {\n    QApplication app(argc, argv);\n    QMainWindow w;\n    QPlainTextEdit *e = new QPlainTextEdit;\n    w.setCentralWidget(e);\n    w.resize(800,600);\n    w.show();\n    return app.exec();\n}\n")
endif()

# Qt setup
find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SRC src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# "make run" target
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building and running ${PROJECT_NAME}..."
)

