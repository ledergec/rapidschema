# Copyright (C) 2019 Christian Ledergerber
set(RAPIDSCHEMA_UNITTEST_TARGET rapidschema_unittest)

file(GLOB UNITTEST_SRC
    "rapidschema/*.h"
    "rapidschema/*.cpp"
)

add_executable(${RAPIDSCHEMA_UNITTEST_TARGET} ${UNITTEST_SRC})

if (RAPIDSCHEMA_CPP_11)
    target_link_libraries(${RAPIDSCHEMA_UNITTEST_TARGET} gtest gmock fmt absl::optional)
else()
    target_link_libraries(${RAPIDSCHEMA_UNITTEST_TARGET} gtest gmock fmt)
endif()

set_target_properties(${RAPIDSCHEMA_UNITTEST_TARGET} PROPERTIES COMPILE_FLAGS ${RAPIDSCHEMA_COMPILE_FLAGS})

setup_cpplint(${RAPIDSCHEMA_UNITTEST_TARGET} ${UNITTEST_SRC})
