find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB TESTS "*.cpp")

add_executable(strumok_tests ${TESTS})

target_include_directories(strumok_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(strumok_tests PRIVATE strumok_lib GTest::gtest_main)

gtest_discover_tests(strumok_tests)