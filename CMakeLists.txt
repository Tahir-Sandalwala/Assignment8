cmake_minimum_required(VERSION 3.5)

project(PipelinedProcessor LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR src)

set(INCLUDE_DIR include)

set(SRC_FILES ${SRC_DIR}/ALU.cpp ${SRC_DIR}/Cache.cpp ${SRC_DIR}/Register.cpp
              ${SRC_DIR}/RegisterFile.cpp ${SRC_DIR}/main.cpp ${SRC_DIR}/IF_Module.cpp)

set(PROJECT_SOURCES ${SRC_FILES})

add_compile_options(-Wall -Wextra -pedantic -Wpedantic -Wshadow -O2)

if(DEFINED ASANITIZED)
  message(STATUS "Compiling with address sanitizer on...")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
