cmake_minimum_required(VERSION 3.5)

project(PipelinedProcessor LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE RelWithDebInfo)
# set(CMAKE_BUILD_TYPE Release)
# SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
# SET(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_BUILD_TYPE Debug)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR src)

set(INCLUDE_DIR include)

set(SRC_FILES
    ${SRC_DIR}/ALU.cpp
    ${SRC_DIR}/Buffers.cpp
    ${SRC_DIR}/Cache.cpp
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Modules.cpp
    ${SRC_DIR}/Processor.cpp
    ${SRC_DIR}/Register.cpp
    ${SRC_DIR}/RegisterFile.cpp
    ${SRC_DIR}/Utility.cpp)

set(PROJECT_SOURCES ${SRC_FILES})

add_compile_options(-Wall -Wextra -pedantic -Wpedantic -Wshadow)

if(DEFINED ASANITIZED)
  message(STATUS "Compiling with address sanitizer on...")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
