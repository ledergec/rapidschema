# Copyright (C) 2019 Christian Ledergerber

file(GLOB_RECURSE RAPID_SCHEMA_SRC
        "rapidschema/*.h"
        "rapidschema/*.cpp"
        )

add_custom_target(rapidschema_library)

setup_cpplint(rapidschema_library ${RAPID_SCHEMA_SRC})
