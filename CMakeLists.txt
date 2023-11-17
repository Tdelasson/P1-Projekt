cmake_minimum_required(VERSION 3.1)
project (P1-projekt)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)
