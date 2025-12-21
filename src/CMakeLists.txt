project(newbie_project LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
# 先创建一个库, 让库的头文件可以被其他目标使用
add_library(newbie_lib ${LIB_SOURCE_FILES})
target_include_directories(newbie_lib PUBLIC
    ${HEADER_PATHS}
)

option(BUILD_NEWBIE "Build the newbie executable" ON)
message(NOTICE "BUILD_NEWBIE=${BUILD_NEWBIE}")

if (BUILD_NEWBIE)
    add_executable(newbie main.cpp)
    target_link_libraries(newbie PRIVATE newbie_lib)
    target_include_directories(newbie PRIVATE
        ${HEADER_PATHS}
    )
endif()