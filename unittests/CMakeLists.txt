
file(GLOB UNITTEST_SRC
    "*.h"
    "*.cpp"
)

add_executable(unittest ${UNITTEST_SRC} transform_result_matchers.h)

target_link_libraries(unittest gtest gmock fmt)

set_target_properties(unittest PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)
