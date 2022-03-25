cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME life)

project(${PROJECT_NAME} VERSION 1.0
             DESCRIPTION "Conway's Game of Life"
             LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Werror -g -Og)

configure_file(version.h.in ../include/${PROJECT_NAME}/version.h)

add_executable(${PROJECT_NAME} ${target_sources})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
                          )

add_subdirectory(src)