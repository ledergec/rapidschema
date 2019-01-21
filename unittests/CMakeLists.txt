# Copyright (C) 2019 Christian Ledergerber

file(GLOB UNITTEST_SRC
    "rapidschema/*.h"
    "rapidschema/*.cpp"
)

add_executable(unittest ${UNITTEST_SRC})

if (RAPIDSCHEMA_CPP_11)
    target_link_libraries(unittest gtest gmock fmt absl::optional)
else()
    target_link_libraries(unittest gtest gmock fmt)
endif()

setup_cpplint(unittest ${UNITTEST_SRC})
