cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_COMPILER "C:/Install/Programming Language/C++/Compiler/winlibs-x86_64-mcf-seh-gcc-13.2.0-llvm-16.0.6-mingw-w64ucrt-11.0.1-r2/mingw64/bin/g++.exe")

project(CS161-Minesweeper VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS main.cpp MainWindow/*.cpp Style/*.cpp Pages/*.cpp Session/* Timer/*.cpp)

set(TARGET_NAME Game)
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(QT6_DIR D:/Unsorted/QT/6.6.0/mingw_64) #replace the directory to your QT/6.6.0/mingw_64
set(QT_COMPONENTS Widgets)
set(CMAKE_PREFIX_PATH ${QT6_DIR})
find_package(Qt6 REQUIRED COMPONENTS ${QT_COMPONENTS})

include_directories(${QT6_DIR}/include . Pages/ Pages/GameboardPage/)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
qt_add_executable(${TARGET_NAME} ${SOURCES} Data/resources.qrc )

foreach(LIB ${QT_COMPONENTS})
    target_link_libraries(${TARGET_NAME} PRIVATE Qt6::${LIB})
endforeach()

set_target_properties(${TARGET_NAME} PROPERTIES WIN32_EXECUTABLE ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/Zc:__cplusplus)
endif()

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