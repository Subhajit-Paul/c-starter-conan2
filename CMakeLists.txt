cmake_minimum_required(VERSION 3.23)
project(c_starter LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(executable src/main.c)
target_include_directories(executable PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(CTest)
if(BUILD_TESTING)
    add_executable(test_main tests/test_main.c)
    target_include_directories(test_main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    add_test(NAME starter_tests COMMAND test_main)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(executable PRIVATE -Wall -Wextra -Wpedantic)
    if(TARGET test_main)
        target_compile_options(test_main PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
