# Copyright (C) 2019 Christian Ledergerber

file(GLOB UNITTEST_SRC
    "rapidschema/*.h"
    "rapidschema/*.cpp"
)

add_executable(unittest ${UNITTEST_SRC})

target_link_libraries(unittest gtest gmock fmt)

setup_cpplint(unittest ${UNITTEST_SRC})
