add_library(adapter SHARED adapter/adapter.cpp)
target_include_directories(adapter PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(bridge SHARED bridge/bridge.cpp)
target_include_directories(bridge PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(STRUCTURAL_LIBRARIES adapter bridge PARENT_SCOPE)
