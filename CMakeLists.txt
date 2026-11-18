cmake_minimum_required(VERSION 3.23)
project(c_starter LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(pyc INTERFACE)
target_include_directories(pyc INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(demo src/main.c)
target_link_libraries(demo PRIVATE pyc)

include(CTest)
if(BUILD_TESTING)
    add_executable(test_pyc tests/test_pyc.c)
    target_link_libraries(test_pyc PRIVATE pyc)
    add_test(NAME pyc_vector COMMAND test_pyc)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(demo PRIVATE -Wall -Wextra -Wpedantic)
    if(TARGET test_pyc)
        target_compile_options(test_pyc PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
