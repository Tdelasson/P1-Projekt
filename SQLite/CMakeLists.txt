add_library(sqlite3c sqlite3.c)
add_library(sqlite3ext sqlite3ext.h)
add_library(sqlite3h sqlite3.h)

add_executable(Database Database_interaction.c)
add_executable(shell shell.c)
add_executable(sqlite3c shell.c)


link_directories(/path/to/sqlite/library)
target_link_libraries(Database sqlite3c)