# Copyright (C) 2019 Christian Ledergerber

set(EXAMPLES
    simple_parse
    simple_error
    simple_serialization
    simple_schema)

foreach (example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    if (RAPIDSCHEMA_CPP_11)
        target_link_libraries(${example} fmt absl::optional)
    else()
        target_link_libraries(${example} fmt)
    endif()
    setup_cpplint(${example} ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp)
endforeach()

