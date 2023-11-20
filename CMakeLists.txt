cmake_minimum_required(VERSION 3.26)
project(P1-Projekt)


add_executable(database_interaction database_interaction.c)
add_library(sqlite3 sqlite3.c)
target_link_libraries(database_interaction sqlite3)

