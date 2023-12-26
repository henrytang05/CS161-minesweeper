cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

project(CS161-Minesweeper VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX /Zc:__cplusplus /permissive-)
endif()


FILE(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

set(TARGET_NAME Game)
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(QT6_DIR ${PROJECT_SOURCE_DIR}/QT6/mingw_64) #replace the directory to your QT/6.6.0/mingw_64
set(CMAKE_PREFIX_PATH ${QT6_DIR})
set(QT_COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS ${QT_COMPONENTS})

include_directories(${QT6_DIR}/include src/ src/Pages/ src/Pages/GameboardPage/)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
qt_add_executable(${TARGET_NAME} ${SOURCES} src/resources.qrc)

foreach(LIB ${QT_COMPONENTS})
    target_link_libraries(${TARGET_NAME} PRIVATE Qt6::${LIB})
endforeach()

set_target_properties(${TARGET_NAME} PROPERTIES WIN32_EXECUTABLE ON)



set(BUILD_DIR ${PROJECT_SOURCE_DIR}/build)
set(DIST_DIR ${BUILD_DIR}/dist)
set(CMAKE_INSTALL_PREFIX ${DIST_DIR})

install(TARGETS ${TARGET_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET ${TARGET_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)