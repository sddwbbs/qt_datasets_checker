cmake_minimum_required(VERSION 3.22)
project(qt_http_service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_http_service main.cpp)
target_link_libraries(qt_http_service
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

