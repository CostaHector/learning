cmake_minimum_required(VERSION 3.14)
project(newbie LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

## way1. file(DOWNLOAD url downloadedPath) 方式, 有进度, 但过程比较复杂
set(GTEST_VERSION "1.15.0")
set(GTEST_URL "https://github.com/google/googletest/releases/download/v1.15.0/googletest-1.15.0.tar.gz")

# 设置下载到/解压到的路径
SET(THIRD_PARTY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(GOOGLE_TEST_TAR_GZ ${THIRD_PARTY_PATH}/googletest.tar.gz)
SET(GOOGLE_TEST_VERSION_PATH ${THIRD_PARTY_PATH}/googletest-${GTEST_VERSION})
SET(GOOGLE_TEST_PATH ${THIRD_PARTY_PATH}/googletest)

if(NOT EXISTS ${GOOGLE_TEST_PATH})
    if (NOT EXISTS ${THIRD_PARTY_PATH})
        file(MAKE_DIRECTORY ${THIRD_PARTY_PATH} RESULT mkdir_result OUTPUT mkdir_output)
        message(STATUS "Create path[${THIRD_PARTY_PATH}]...{mkdir_result} {mkdir_output}")
    endif()

    if(EXISTS ${GOOGLE_TEST_TAR_GZ})
        file(REMOVE ${GOOGLE_TEST_TAR_GZ} RESULT remove_result OUTPUT remove_output)
        message(STATUS "removing old tar.gz file [${GOOGLE_TEST_TAR_GZ}]... ${remove_result} ${remove_output}")
    endif()

    message(NOTICE "\t> 1. Downloading googletest from url[${GTEST_URL}] and save into[${GOOGLE_TEST_TAR_GZ}]...")
    file(DOWNLOAD ${GTEST_URL} ${GOOGLE_TEST_TAR_GZ}
            SHOW_PROGRESS
            TIMEOUT 10
            STATUS DOWNLOAD_STATUS) # 返回列表 [code;message], RESULT同STATUS互斥, 只可以指定其中的一个
    list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
    list(GET DOWNLOAD_STATUS 1 STATUS_CODE_MESSAGE)
    if(NOT STATUS_CODE EQUAL 0)
        message(FATAL_ERROR "Failed to download googletest. error code[${DOWNLOAD_STATUS}]")
    endif()
    message(STATUS "Downloaded finished. See in[${GOOGLE_TEST_TAR_GZ}]")

    # 检查文件大小
    file(SIZE ${GOOGLE_TEST_TAR_GZ} FILE_SIZE)
    if(FILE_SIZE EQUAL 0)
        message(FATAL_ERROR "File [${GOOGLE_TEST_TAR_GZ}] downloaded is empty")
    endif()
    message(STATUS "Download successful! File[${GOOGLE_TEST_TAR_GZ}] size: ${FILE_SIZE} bytes")

    message(NOTICE "\t> 2. Extracting googletest tar.gz file into path[${THIRD_PARTY_PATH}] ...")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${GOOGLE_TEST_TAR_GZ}
            WORKING_DIRECTORY ${THIRD_PARTY_PATH}
            RESULT_VARIABLE untar_result
            OUTPUT_VARIABLE untar_output
            ERROR_VARIABLE untar_error
    )
    if(NOT untar_result EQUAL 0)
        message(FATAL_ERROR "Failed to extract googletest tar.gz file. error code: ${untar_result}, output: ${untar_output}, error: ${untar_error}")
    endif()
    if (NOT EXISTS ${GOOGLE_TEST_VERSION_PATH})
        message(FATAL_ERROR "Extracted googletest.tar.gz to destination folder not found: ${GOOGLE_TEST_VERSION_PATH}")
    endif()

    message(NOTICE "\t> 3. Renaming extracted folder to remove version info ...")
    file(RENAME ${GOOGLE_TEST_VERSION_PATH} ${GOOGLE_TEST_PATH} RESULT rename_result OUTPUT rename_output)
    if(NOT rename_result EQUAL 0)
        message(FATAL_ERROR "Failed to rename googletest folder. error code: ${rename_result}, output: ${rename_output}")
    endif()
endif()

## way2. 使用 FetchContent 模块, 无进度, 但是简单)(下载到build/_deps目录下)
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/releases/download/v1.15.0/googletest-1.15.0.tar.gz
# )
# FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(testcase)
add_subdirectory(${GOOGLE_TEST_PATH})