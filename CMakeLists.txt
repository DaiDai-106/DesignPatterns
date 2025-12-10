cmake_minimum_required(VERSION 3.20)
project(DesignPatterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SHARED_LIB "Build shared library or not. Otherwise, build static instead." ON)
option(RUN_CREATIONAL "Run creational design pattern code examples." ON)
option(RUN_STRUCTURAL "Run structural design pattern code examples." ON)


message(STATUS "========== ${PROJECT_NAME} Build Information ==========")
message(STATUS "Current build options:")
message(STATUS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "-DSHARED_LIB=${SHARED_LIB}")
message(STATUS "-DRUN_CREATIONAL=${RUN_CREATIONAL}")
message(STATUS "-DRUN_STRUCTURAL=${RUN_STRUCTURAL}")
message(STATUS "========== ${PROJECT_NAME} Build Information ==========")

set(CREATIONAL_LIBRARIES)
set(STRUCTURAL_LIBRARIES) # Initialize STRUCTURAL_LIBRARIES as well
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)

if(RUN_CREATIONAL)
    add_subdirectory( ${CMAKE_SOURCE_DIR}/src/creational)
    
    # 收集 Creational 相关的测试源文件
    list(APPEND TEST_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/factory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/prototype.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/singleton.cpp
    )
endif()

if(RUN_STRUCTURAL)
    add_subdirectory( ${CMAKE_SOURCE_DIR}/src/structural)

    # 收集 Structural 相关的测试源文件
    list(APPEND TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/test/structural/adapter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/structural/bridge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/structural/composite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/structural/facade.cpp
    )
endif()

# 统一生成一个测试可执行文件
add_executable(design_patterns_test ${TEST_SOURCES})

# 链接所有相关库
target_link_libraries(design_patterns_test PRIVATE 
    ${CREATIONAL_LIBRARIES}
    ${STRUCTURAL_LIBRARIES}
)
