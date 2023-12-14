add_executable(tests tests.c)
target_link_libraries(tests database_interaction)
target_link_libraries(tests pillbox)
target_link_libraries(tests Calculator)

add_test(NAME tests
        COMMAND tests)

# Set the working directory for the test
set_tests_properties(tests PROPERTIES
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/database_textfiles"
)