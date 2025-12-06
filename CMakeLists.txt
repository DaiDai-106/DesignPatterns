cmake_minimum_required(VERSION 3.20)
project(DesignPatterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SHARED_LIB "Build shared library or not. Otherwise, build static instead." ON)
option(RUN_BUILDER "Run builder design pattern code examples." ON)


message(STATUS "========== ${PROJECT_NAME} Build Information ==========")
message(STATUS "Current build options:")
message(STATUS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "-DSHARED_LIB=${SHARED_LIB}")
message(STATUS "-DRUN_BUILDER=${RUN_BUILDER}")
message(STATUS "========== ${PROJECT_NAME} Build Information ==========")

set(BUILDER_LIBRARIES)
if(RUN_BUILDER)
    add_subdirectory( ${CMAKE_SOURCE_DIR}/src/builder)
    add_executable(test_builder ${CMAKE_CURRENT_SOURCE_DIR}/test/builder.cpp)
    target_link_libraries(test_builder PRIVATE ${BUILDER_LIBRARIES})
endif()

