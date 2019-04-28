# Copyright (C) 2019 Christian Ledergerber

cmake_minimum_required (VERSION 3.5)
project (rapidschema)

find_package(Doxygen
        REQUIRED dot
        OPTIONAL_COMPONENTS mscgen dia)

option(RAPIDSCHEMA_CPP_11 "Build rapidschema with cpp 11" OFF)
option(RAPIDSCHEMA_WITH_SCHEMA_GENERATION "Build rapidschema including schema generation")
option(RAPIDSCHEMA_WITH_CONCEPTS "Build rapidschema with gcc and -fconcepts")

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cpplint/cpplint.cmake)

set(RAPIDSCHEMA_COMPILE_FLAGS "-Wall -Werror -Wpedantic -DRAPIDJSON_HAS_STDSTRING")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   set(RAPIDSCHEMA_COMPILE_FLAGS "${RAPIDSCHEMA_COMPILE_FLAGS} -Wno-unused-command-line-argument")
endif()

if (${RAPIDSCHEMA_WITH_CONCEPTS})
   set(RAPIDSCHEMA_COMPILE_FLAGS "${RAPIDSCHEMA_COMPILE_FLAGS} -fconcepts -DRAPIDSCHEMA_WITH_CONCEPTS")
endif()

if (RAPIDSCHEMA_CPP_11)
   set(RAPIDSCHEMA_COMPILE_FLAGS "${RAPIDSCHEMA_COMPILE_FLAGS} -std=c++11 -DRAPIDSCHEMA_CPP_11")
else()
   set(RAPIDSCHEMA_COMPILE_FLAGS "${RAPIDSCHEMA_COMPILE_FLAGS} -std=c++1z")
endif()

if (RAPIDSCHEMA_WITH_SCHEMA_GENERATION)
   set(RAPIDSCHEMA_COMPILE_FLAGS "${RAPIDSCHEMA_COMPILE_FLAGS} -DRAPIDSCHEMA_WITH_SCHEMA_GENERATION")
endif()

set(RAPIDJSON_BUILD_TESTS "OFF" CACHE STRING "Turn off rapidjson tests to avoid redefinition of gtest target")

enable_testing()

# add all source code directories
if (RAPIDSCHEMA_CPP_11)
   include_directories(extern/abseil)
endif()
include_directories(extern/rapidjson/include)
include_directories(extern/fmt/include)
include_directories(include)
include_directories(unittests)
include(extern/cmake-doxygen/cmake/cmake-doxygen.cmake)

add_subdirectory(extern/googletest)
if (RAPIDSCHEMA_CPP_11)
   add_subdirectory(extern/abseil)
endif()
add_subdirectory(extern/rapidjson)
add_subdirectory(extern/fmt)
add_subdirectory(include)
add_subdirectory(unittests)
add_subdirectory(examples)
