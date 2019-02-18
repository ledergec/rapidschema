# Copyright (C) 2019 Christian Ledergerber

if (NOT ${RAPIDSCHEMA_CPP_11} AND ${RAPIDSCHEMA_WITH_SCHEMA_GENERATION})

    set(EXAMPLES
        simple_parse
        simple_error
        simple_serialization
        simple_schema
        schema_generation)

    foreach (example ${EXAMPLES})
        add_executable(${example} ${example}.cpp)
        target_link_libraries(${example} fmt rapidschema)
        set_target_properties(${example} PROPERTIES COMPILE_FLAGS ${RAPIDSCHEMA_COMPILE_FLAGS})
        setup_cpplint(${example} ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp)
    endforeach()

endif()