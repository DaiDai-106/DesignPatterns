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
set(STRUCTURAL_LIBRARIES)

if(RUN_CREATIONAL)
    add_subdirectory( ${CMAKE_SOURCE_DIR}/src/creational)
    
    add_executable(test_builder ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/builder.cpp)
    target_link_libraries(test_builder PRIVATE ${CREATIONAL_LIBRARIES})

    add_executable(test_factory ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/factory.cpp)
    target_link_libraries(test_factory PRIVATE ${CREATIONAL_LIBRARIES})

    add_executable(test_prototype ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/prototype.cpp)
    target_link_libraries(test_prototype PRIVATE ${CREATIONAL_LIBRARIES})

    add_executable(test_singleton ${CMAKE_CURRENT_SOURCE_DIR}/test/creational/singleton.cpp)
    target_link_libraries(test_singleton PRIVATE ${CREATIONAL_LIBRARIES})
endif()

if(RUN_STRUCTURAL)
    add_subdirectory( ${CMAKE_SOURCE_DIR}/src/structural)
    
    add_executable(test_adapter ${CMAKE_CURRENT_SOURCE_DIR}/test/structural/adapter.cpp)
    target_link_libraries(test_adapter PRIVATE ${STRUCTURAL_LIBRARIES})

    add_executable(test_bridge ${CMAKE_CURRENT_SOURCE_DIR}/test/structural/bridge.cpp)
    target_link_libraries(test_bridge PRIVATE ${STRUCTURAL_LIBRARIES})
endif()
