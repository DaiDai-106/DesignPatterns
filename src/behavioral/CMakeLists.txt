add_library(responsibility_chain SHARED responsibility_chain/responsibility_chain.cpp)
target_include_directories(responsibility_chain PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(commandd SHARED commandd/commandd.cpp)
target_include_directories(commandd PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(BEHAVIORAL_LIBRARIES responsibility_chain commandd PARENT_SCOPE)