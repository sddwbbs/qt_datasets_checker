cmake_minimum_required(VERSION 3.10)
project(qt_http_service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(KF5WidgetsAddons REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS WebEngineWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES main.cpp mainwindow.cpp authorization.cpp registration.cpp download.cpp DataModel.cpp MdiChild.cpp)
set(UI_FILES authorization.ui mainwindow.ui registration.ui)

# Создаем массив для хранения исходных файлов UI
set(GENERATED_UI_HEADERS)

# Перебираем каждый файл из списка UI_FILES и добавляем команду для его генерации
foreach(UI_FILE ${UI_FILES})
    # Получаем путь к исходному файлу UI
    get_filename_component(UI_FILENAME ${UI_FILE} NAME_WE)

    # Указываем путь к сгенерированному файлу UI
    set(GENERATED_UI_HEADER ${CMAKE_CURRENT_BINARY_DIR}/ui_${UI_FILENAME}.h)

    # Добавляем команду для генерации файла UI
    add_custom_command(
            OUTPUT ${GENERATED_UI_HEADER}
            COMMAND uic -o ${GENERATED_UI_HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/${UI_FILE}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${UI_FILE}
    )

    # Добавляем сгенерированный файл в массив
    list(APPEND GENERATED_UI_HEADERS ${GENERATED_UI_HEADER})
endforeach()

# Use qmake to get the path to the Qt plugins directory
execute_process(
        COMMAND qmake -query QT_INSTALL_PLUGINS
        OUTPUT_VARIABLE QT_PLUGINS_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Add the PostgreSQL driver to your project
set(QT5_MODULE_PATH "${QT_PLUGINS_DIR}/sqldrivers")

add_library(qsqlpsql MODULE IMPORTED)
set_target_properties(qsqlpsql PROPERTIES
        IMPORTED_LOCATION "${QT5_MODULE_PATH}/libqsqlpsql.so"  # Adjust the extension based on your system (e.g., .dylib on macOS)
        )

# Создаем исполняемый файл qt_http_service с использованием массива сгенерированных файлов UI
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${GENERATED_UI_HEADERS})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Sql
        KF5::WidgetsAddons
        Qt5::WebEngineWidgets
        pq
        )
