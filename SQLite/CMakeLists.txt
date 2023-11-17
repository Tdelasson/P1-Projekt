add_library(sqlite3 sqlite3.exe)

add_executable(Database_interaction Database_interaction.c)
target_link_libraries(Database_interaction sqlite3)
