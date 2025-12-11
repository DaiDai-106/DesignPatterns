add_library(adapter SHARED adapter/adapter.cpp)
target_include_directories(adapter PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(bridge SHARED bridge/bridge.cpp)
target_include_directories(bridge PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(composite SHARED composite/composite.cpp)
target_include_directories(composite PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(facade SHARED facade/facade.cpp)
target_include_directories(facade PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(flyweight SHARED flyweight/flyweight.cpp)
target_include_directories(flyweight PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(proxy SHARED proxy/proxy.cpp)
target_include_directories(proxy PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(STRUCTURAL_LIBRARIES adapter bridge composite facade flyweight proxy PARENT_SCOPE)
