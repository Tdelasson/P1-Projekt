add_library(functions_main functions_main.c)

add_executable(main main.c)
target_link_libraries(main functions_main.c)
