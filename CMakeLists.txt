cmake_minimum_required(VERSION 3.26)
project(P1-Projekt)


add_executable(database_interaction src/database_interaction.c)
add_library(sqlite3 src/sqlite3.c)
target_link_libraries(database_interaction sqlite3)

