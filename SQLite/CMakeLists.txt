
link_directories(/path/to/sqlite/library)
add_executable(Database Database_interaction.c)
target_link_libraries(Database sqlite3)