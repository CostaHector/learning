project(tester_project LANGUAGES CXX)

message(STATUS "in testcase folder cmakelists.txt")
message(STATUS "HOME=$ENV{HOME}")
message(STATUS "Global: ${CMAKE_BINARY_DIR}; ${CMAKE_SOURCE_DIR}")
message(STATUS "Itself: ${CMAKE_CURRENT_BINARY_DIR}; ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Itself: ${CMAKE_CURRENT_SOURCE_DIR}, ${CMAKE_CURRENT_LIST_DIR}, ${CMAKE_CURRENT_LIST_FILE}")
message(STATUS "Project Itself: ${PROJECT_NAME}, ${PROJECT_SOURCE_DIR}, ${PROJECT_BINARY_DIR}")
message(STATUS "Project Itself: ${tester_project_SOURCE_DIR}, ${tester_project_BINARY_DIR}")

file(GLOB TEST_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)
message(STATUS "TEST_SOURCE_FILES=${TEST_SOURCE_FILES}")
option(BUILD_TESTER "Build the tester executable" OFF)
message(NOTICE "BUILD_TESTER=${BUILD_TESTER}")
if (BUILD_TESTER)
    add_executable(tester ${TEST_SOURCE_FILES})
    target_link_libraries(tester newbie_lib gtest gtest_main mockcpp)
endif()

# 启用CMAKE_EXPORT_COMPILE_COMMANDS后, 执行cmake -S . -B build时会生成compile_commands.json, 里面记录了每个源文件的完整编译命, 
# vscode 从-I参数中提取所有头文件路径使用, 从-D参数中获取宏定义, 从-std=c++17知道使用C++17, 知道使用/usr/bin/g++
# 从而确保vscode遵循cmake配置进行准确的符号/名称查找

# CMake 提供了多个路径相关的变量，用于在构建过程中定位源代码、构建输出、当前处理文件等位置。以下是一些常用的路径变量：
# CMAKE_SOURCE_DIR: 顶级 CMakeLists.txt 所在的源目录路径。
# CMAKE_BINARY_DIR: 顶级构建目录的路径，即运行 CMake 生成构建文件的目录。
# CMAKE_CURRENT_SOURCE_DIR: 当前正在处理的 CMakeLists.txt 所在的目录。
# CMAKE_CURRENT_BINARY_DIR: 与当前 CMakeLists.txt 对应的构建目录。
# CMAKE_CURRENT_LIST_DIR: 当前正在处理的 CMake 文件（可能是 CMakeLists.txt 或通过 include() 加载的 .cmake 文件）所在的目录。
# CMAKE_CURRENT_LIST_FILE: 当前正在处理的 CMake 文件的完整路径。
# CMAKE_MODULE_PATH: 用于指定查找 CMake 模块的路径列表。
# CMAKE_PREFIX_PATH: 用于查找依赖包、程序、库的搜索路径列表。
# CMAKE_INSTALL_PREFIX: 安装目标文件时的根目录，默认为 /usr/local（Unix）或 C:\Program Files（Windows）。
# PROJECT_SOURCE_DIR: 当前项目（最近一次 project() 命令定义）的源目录。
# PROJECT_BINARY_DIR: 当前项目对应的构建目录。
# <PROJECT-NAME>_SOURCE_DIR: 指定项目名称（由 project() 定义）的源目录，例如如果项目名为 MyProject，则变量为 MyProject_SOURCE_DIR。
# <PROJECT-NAME>_BINARY_DIR: 指定项目名称的构建目录。
# EXECUTABLE_OUTPUT_PATH: 控制可执行文件输出目录的变量。
# LIBRARY_OUTPUT_PATH: 控制库文件输出目录的变量。
# 关于 CMAKE_SOURCE_DIR 和 CMAKE_BINARY_DIR
# CMAKE_SOURCE_DIR​ 和 CMAKE_BINARY_DIR​ 确实可以通过 cmake -S -B命令指定。例如，执行 cmake -S . -B build时：
# -S .指定源代码目录为当前目录（.），因此 CMAKE_SOURCE_DIR​ 被设置为 .的绝对路径。
# -B build指定构建目录为 ./build，因此 CMAKE_BINARY_DIR​ 被设置为 ./build的绝对路径。
# 如果使用传统方式，在构建目录中运行 cmake <path-to-source>，则 CMAKE_BINARY_DIR​ 为当前工作目录（构建目录），CMAKE_SOURCE_DIR​ 为指定的源路径。
# 这两个变量在整个项目层次结构（包括所有通过 add_subdirectory()添加的子目录）中保持不变，始终指向顶级源目录和顶级构建目录。即使进入子目录的 CMakeLists.txt，它们的值也不会改变。如需获取当前处理的 CMakeLists.txt 所在目录，应使用 CMAKE_CURRENT_SOURCE_DIR​ 和 CMAKE_CURRENT_BINARY_DIR。