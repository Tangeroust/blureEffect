cmake_minimum_required(VERSION 3.20)
project(testProgram VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.12/5.12.12/msvc2017_64/lib/cmake")
find_package(QT NAMES Qt5 COMPONENTS Widgets WebEngineWidgets WebEngine REQUIRED)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(testProgram main.cpp)
target_link_libraries(testProgram
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )