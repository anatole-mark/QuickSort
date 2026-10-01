cmake_minimum_required(VERSION 3.31)
project(QuickSort)

set(CMAKE_CXX_STANDARD 20)

add_executable(QuickSort src/main.cpp)
target_include_directories(QuickSort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_subdirectory(tests)
