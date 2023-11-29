add_executable(main main.c)
add_library(functions_main functions_main.c)


target_link_libraries(main functions_main)
target_link_libraries(main database_interaction)
target_link_libraries(main pillbox)