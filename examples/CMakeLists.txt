# Copyright (C) 2019 Christian Ledergerber

set(EXAMPLES
    simple_parse
    simple_error
    simple_serialization
    simple_schema)

foreach (example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} fmt)
    setup_cpplint(${example} ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp)
endforeach()

