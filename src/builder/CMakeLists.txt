add_library(builder SHARED combine_builder.cpp)
target_include_directories(builder PUBLIC ${CMAKE_SOURCE_DIR}/include)
set(BUILDER_LIBRARIES builder PARENT_SCOPE)
