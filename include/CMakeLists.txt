# Copyright (C) 2019 Christian Ledergerber

file(GLOB_RECURSE RAPID_SCHEMA_SRC
        "rapidschema/*.h"
        "rapidschema/*.cpp"
        )

add_library(rapidschema_library STATIC ${RAPID_SCHEMA_SRC})
set_target_properties(rapidschema_library PROPERTIES COMPILE_FLAGS ${RAPIDSCHEMA_COMPILE_FLAGS})

setup_cpplint(rapidschema_library ${RAPID_SCHEMA_SRC})
