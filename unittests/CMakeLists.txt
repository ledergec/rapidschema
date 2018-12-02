
file(GLOB UNITTEST_SRC
    "rapidschema/*.h"
    "rapidschema/*.cpp"
)

add_executable(unittest ${UNITTEST_SRC} ../include/rapidschema/meta/type_set.h rapidschema/meta/type_set_test.cpp)

target_link_libraries(unittest gtest gmock fmt)

set_target_properties(unittest PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
        )

add_dependencies(unittest ${CPPLINT_TARGET})
