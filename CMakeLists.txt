cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME life)

project(${PROJECT_NAME} VERSION 1.0
             DESCRIPTION "Conway's Game of Life"
             LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Werror -g -Og)

configure_file(version.h.in ../include/${PROJECT_NAME}/version.h)

find_package(Qt6 COMPONENTS Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} ${target_sources})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
                          )

target_link_libraries(${PROJECT_NAME} Qt6::Gui Qt6::Widgets)

add_subdirectory(src)