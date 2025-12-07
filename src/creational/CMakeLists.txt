add_library(builder SHARED builder/combine_builder.cpp)
target_include_directories(builder PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(factory SHARED factory/factory.cpp factory/abstract_factory.cpp)
target_include_directories(factory PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(prototype SHARED prototype/prototype.cpp)
target_include_directories(prototype PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(CREATIONAL_LIBRARIES builder factory prototype PARENT_SCOPE)
