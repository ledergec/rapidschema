# Copyright (C) 2019 Christian Ledergerber

file(GLOB_RECURSE RAPID_SCHEMA_SRC
        "rapidschema/*.h"
        "rapidschema/*.cpp"
        )

add_library(rapidschema STATIC ${RAPID_SCHEMA_SRC})
set_target_properties(rapidschema PROPERTIES COMPILE_FLAGS ${RAPIDSCHEMA_COMPILE_FLAGS})

setup_cpplint(rapidschema ${RAPID_SCHEMA_SRC})

if(${DOXYGEN_FOUND})
    DOXYGEN(TARGET "rapidschema_doxygen"
            OUTPUT_DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}/doc"
            SOURCES "${RAPID_SCHEMA_SRC}"
            NO
            GENERATE_LATEX
            VERBATIM_HEADERS
            EXTRACT_ALL
            WARN_IF_UNDOCUMENTED
            YES
            CALL_GRAPH
            EXTRACT_STATIC
            GENERATE_TREEVIEW
            HAVE_DOT
            INTERACTIVE_SVG
            JAVADOC_AUTOBRIEF
            OPTIMIZE_OUTPUT_FOR_C
            RECURSIVE
            WARN_AS_ERROR
            WARN_IF_ERROR
            WARN_NO_PARAMDOC
            WARN_IF_DOC_ERROR
            PREDEFINED
            __DOXYGEN
            EXCLUDE_SYMBOLS
            __stringify_1
            TAB_SIZE 8
            DOT_FONTSIZE 12
            DOT_IMAGE_FORMAT svg)
endif()
