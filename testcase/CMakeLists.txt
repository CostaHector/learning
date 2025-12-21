project(tester_project LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB TEST_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)
message(STATUS "TEST_SOURCE_FILES=${TEST_SOURCE_FILES}")
add_executable(tester ${TEST_SOURCE_FILES})
target_link_libraries(tester newbie_lib gtest gtest_main gmock)

# 启用CMAKE_EXPORT_COMPILE_COMMANDS后, 执行cmake -S . -B build时会生成compile_commands.json, 里面记录了每个源文件的完整编译命, 
# vscode 从-I参数中提取所有头文件路径使用, 从-D参数中获取宏定义, 从-std=c++17知道使用C++17, 知道使用/usr/bin/g++
# 从而确保vscode遵循cmake配置进行准确的符号/名称查找