cmake_minimum_required(VERSION 3.26)
project(P1-Projekt)



add_library(sqlite3 sqlite3.c sqlite3.h)
add_executable(Database_interaction Database_interaction.c)
target_link_libraries(Database_interaction sqlite3)

