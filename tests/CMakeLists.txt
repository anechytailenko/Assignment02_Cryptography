include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(strumok_tests 
        test-strumok256.cpp 
        test-strumok512.cpp
        test-attack.cpp
)

target_include_directories(strumok_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(strumok_tests PRIVATE strumok_lib gtest_main)

gtest_discover_tests(strumok_tests)

add_custom_target(run_tests
        COMMAND strumok_tests
        DEPENDS strumok_tests
        COMMENT "Running Strumok Tests..."
        USES_TERMINAL
)