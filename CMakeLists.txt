cmake_minimum_required(VERSION 3.26)
project(P1-Projekt)


<<<<<<< HEAD
add_library(sqlite3 sqlite3.c)
add_executable(Database_interaction Database_interaction.c)
target_link_libraries(Database_interaction sqlite3)
=======
add_executable(database_interaction src/database_interaction.c)
add_library(sqlite3 src/sqlite3.c)
target_link_libraries(database_interaction sqlite3)
>>>>>>> 33b28333eda4c10fd3a4eb73191936ce5f17d55d

