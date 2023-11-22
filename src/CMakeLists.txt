add_subdirectory(test)
add_subdirectory(main)



add_library(Functions_main Main/Functions_main.c)

add_executable(Main Main/Main.c)
target_link_libraries(Main Functions_main)



