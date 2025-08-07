cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(HelloWorld VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(helloworld main.cpp)

# target_include_directories(helloworld PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# add_executable(helloworld2 main.cpp)