project(UnitTests)

add_subdirectory(external/catch2)

set(TEST_MODULES 
    "test_boolean.cppm"
    #    "test_decimal.cppm"
    "test_integer.cppm"
    #"test_stream.cppm"
)

set(TEST_INCLUDE_DIRS "external/catch2/src")

add_executable(${PROJECT_NAME})

target_sources(
  ${PROJECT_NAME}
  PUBLIC
  PUBLIC FILE_SET CXX_MODULES FILES ${TEST_MODULES})

target_include_directories(${PROJECT_NAME} PUBLIC ${TEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain nhtypes)

list(APPEND CMAKE_MODULE_PATH external/catch2/extras)

enable_testing()
include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

add_custom_target(
  AllTests ALL
  COMMAND ${CMAKE_CTEST_COMMAND} ${CMAKE_BINARY_DIR}
  DEPENDS ${PROJECT_NAME}
  COMMENT "Running tests")
