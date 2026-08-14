cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  nhtypes
  VERSION 1.0
  DESCRIPTION "Introduces Integers/Decimals and Booleans with runtime error checking"
  LANGUAGES CXX)

set(MODULES 
    "src/types.cppm"
    "src/common.cppm"
    "src/boolean.cppm"
    "src/decimals.cppm"
    "src/integers.cppm"
    "src/stream.cppm" 
)

add_library(${PROJECT_NAME})

if (NH_NAMESPACE)
    string(SUBSTRING "${NH_NAMESPACE}" 0 1 firstChar)
    string(REPLACE "\"" "" RefinedString "${NH_NAMESPACE}")
    add_compile_definitions(NH_NAMESPACE=${RefinedString})
else()
    add_compile_definitions(NH_NAMESPACE=nh)
endif()


target_sources(
  ${PROJECT_NAME}
  PUBLIC
  PUBLIC FILE_SET CXX_MODULES FILES ${MODULES})

if(BUILD_TESTS)
    add_compile_definitions(ENABLE_TESTABLE_ASSERTIONS)
  add_subdirectory(tests)
endif()

