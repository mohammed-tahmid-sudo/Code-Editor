cmake_minimum_required(VERSION 3.16)
project(CodeEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure folder structure
file(MAKE_DIRECTORY
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/resources/themes
)

# Create main.cpp if missing
set(MAIN_CPP ${CMAKE_SOURCE_DIR}/src/main.cpp)
if(NOT EXISTS ${MAIN_CPP})
    file(WRITE ${MAIN_CPP} "#include <QApplication>\n#include <Qsci/qsciscintilla.h>\n#include <Qsci/qscilexercpp.h>\n\nint main(int argc, char *argv[]) {\n    QApplication app(argc, argv);\n    QsciScintilla editor;\n    QsciLexerCPP *lexer = new QsciLexerCPP;\n    editor.setLexer(lexer);\n    editor.setMarginLineNumbers(1, true);\n    editor.setMarginWidth(1, 40);\n    editor.setUtf8(true);\n    editor.setText(\"// C++ syntax highlighting example\\nint main() {\\n    return 0;\\n}\\n\");\n    editor.resize(800, 600);\n    editor.show();\n    return app.exec();\n}\n")
endif()

# Qt6 Widgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Gather sources
file(GLOB_RECURSE SRC src/*.cpp src/*.h)

# Create executable
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src /usr/include/Qsci)

# Link Qt6 and QScintilla manually
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets /usr/lib/x86_64-linux-gnu/libqscintilla2_qt6.so)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# make run target
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building and running ${PROJECT_NAME}..."
)

