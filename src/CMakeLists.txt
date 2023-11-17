add_library(Functions_main Functions_main.c)


add_executable(Main Main.c)
target_link_libraries(Main Functions_main)


