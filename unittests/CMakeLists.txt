
file(GLOB UNITTEST_SRC
    "rapidschema/*.h"
    "rapidschema/*.cpp"
)

add_executable(unittest ${UNITTEST_SRC})

target_link_libraries(unittest gtest gmock fmt)

set_target_properties(unittest PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
        )

setup_cpplint(unittest ${UNITTEST_SRC} ${HDR_BINARY})
