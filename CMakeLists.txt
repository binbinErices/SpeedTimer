# cmake版本设置  
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)  
# 声明项目名称与语言
project(demo LANGUAGES C CXX)  

# CMAKE_BUILD_TYPE配置构建类型，默认为空，可以选择Debug 或者 Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(POSITION_INDEPENDENT_CODE 1)

set(THIRD_PATH "./third_party")
#
include_directories(${THIRD_PATH}/fmt/include)
#添加非标准共享库的搜索路径
link_directories(${THIRD_PATH}/fmt/lib)

add_executable(test_main test.cc SpendTimer.cpp SpendTimer.h)
target_link_libraries(test_main
PUBLIC
fmt
)
