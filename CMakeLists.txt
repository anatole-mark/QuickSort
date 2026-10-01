cmake_minimum_required(VERSION 3.31)
project(QuickSort)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        nanobench
        GIT_REPOSITORY https://github.com/martinus/nanobench.git
        GIT_TAG v4.6.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nanobench)

add_executable(QuickSort src/main.cpp)
target_include_directories(QuickSort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(QuickSort PRIVATE nanobench)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_subdirectory(tests)
