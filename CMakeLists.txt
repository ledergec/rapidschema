cmake_minimum_required (VERSION 3.8)

option(test "Build all tests." OFF) # Makes boolean 'test' available.

project (rapidoson)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-unused-local-typedefs -Werror")

include_directories(extern/rapidjson/include)
include_directories(extern/fmt/include)
include_directories(include)

add_subdirectory(extern/googletest)
add_subdirectory(extern/rapidjson)
add_subdirectory(extern/fmt)
add_subdirectory(examples)
add_subdirectory(unittests)

if (test)
   if (APPLE)
      add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
      add_definitions(-D__GLIBCXX__)
   endif (APPLE)

   enable_testing()

   # Include the gtest library. gtest_SOURCE_DIR is available due to
   # 'project(gtest)' above.
   include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()
