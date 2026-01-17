project(newbie_project LANGUAGES CXX)
file(GLOB LIB_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/*.c
)
set(HEADER_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
)
message(STATUS "LIB_SOURCE_FILES=${LIB_SOURCE_FILES}")
message(STATUS "HEADER_PATHS=${HEADER_PATHS}")
message(STATUS "BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}")
# 先创建一个库, 让库的头文件可以被其他目标使用
add_library(newbie_lib SHARED ${LIB_SOURCE_FILES})
set_target_properties(newbie_lib PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)
target_include_directories(newbie_lib PUBLIC ${HEADER_PATHS})

add_executable(newbie main.cpp)
target_link_libraries(newbie PRIVATE newbie_lib)
target_include_directories(newbie PRIVATE
    ${HEADER_PATHS}
)