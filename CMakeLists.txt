cmake_minimum_required(VERSION 3.26)
Project(P1-Project)


add_library(sqlite3 sqlite3.c sqlite3.h)
add_executable(Database_interaction Database/Database_interaction.c)
target_link_libraries(Database_interaction sqlite3)

add_subdirectory(Database)