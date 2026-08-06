cmake_minimum_required(VERSION 3.10)  # 设置最低CMake版本
project(nox VERSION 0.1.48 LANGUAGES CXX)  # 项目名称和版本

set(CMAKE_CXX_STANDARD 14)          # 使用C++14标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制使用该标准
set(CMAKE_CXX_EXTENSIONS OFF)       # 禁用编译器扩展（提高可移植性）

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall                    # 开启所有警告
    -Wextra                  # 开启额外警告
    -O2                      # 优化级别（Release模式）
)

message(STATUS "Building ${PROJECT_NAME} version ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")