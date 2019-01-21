# Copyright (C) 2019 Christian Ledergerber

cmake_minimum_required (VERSION 3.8)
project (rapidschema)


option(test "Build all tests." OFF) # Makes boolean 'test' available.
option(RAPIDSCHEMA_CPP_11 "Build rapidschema with cpp 11" OFF)


set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -std=gnu++2a -DRAPIDJSON_HAS_STDSTRING")
# TODO(cledergerber) how is abseil correctly integrated so not all the errors have to be switched off globally?
if (RAPIDSCHEMA_CPP_11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers -Wno-unused-parameter -Wno-pedantic")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-class-memaccess -std=c++11 -DRAPIDSCHEMA_CPP_11")
endif()

# TODO(cledergerber) having to turn off unused-variable in order to compile rapidjson in release seems weired
if (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR  ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
endif()

if (${RAPIDSCHEMA_WITH_CONCEPTS})
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts -DRAPIDSCHEMA_WITH_CONCEPTS")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cpplint/cpplint.cmake)

# add all source code directories
if (RAPIDSCHEMA_CPP_11)
   include_directories(extern/abseil)
endif()
include_directories(extern/rapidjson/include)
include_directories(extern/fmt/include)
include_directories(include)
include_directories(unittests)

add_subdirectory(extern/googletest)
if (RAPIDSCHEMA_CPP_11)
   add_subdirectory(extern/abseil)
endif()
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
