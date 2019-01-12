# Copyright (C) 2019 Christian Ledergerber

cmake_minimum_required (VERSION 3.8)

option(test "Build all tests." OFF) # Makes boolean 'test' available.

project (rapidschema)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -std=gnu++2a -DRAPIDJSON_HAS_STDSTRING")

if (${RAPIDSCHEMA_WITH_CONCEPTS})
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts -DRAPIDSCHEMA_WITH_CONCEPTS")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cpplint/cpplint.cmake)

# add all source code directories
include_directories(extern/rapidjson/include)
include_directories(extern/fmt/include)
include_directories(include)
include_directories(unittests)

add_subdirectory(extern/googletest)
add_subdirectory(extern/rapidjson)
add_subdirectory(extern/fmt)
add_subdirectory(include)
add_subdirectory(unittests)
add_subdirectory(examples)

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
