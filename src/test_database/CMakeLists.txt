add_executable(test_database test_database.c)
target_link_libraries(test_database database_interaction)

add_test(NAME test_database
        COMMAND test_database)

# Set the working directory for the test
set_tests_properties(test_database PROPERTIES
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/database_textfiles"
)