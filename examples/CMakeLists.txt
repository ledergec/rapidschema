
add_executable(example objecttree.cpp ../include/failure.h)

set_target_properties(example PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)
