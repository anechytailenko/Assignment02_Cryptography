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
)
target_include_directories(strumok_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(strumok_tests PRIVATE strumok_lib gtest_main)
gtest_discover_tests(strumok_tests)

add_custom_target(run_tests
        COMMAND strumok_tests
        DEPENDS strumok_tests
        COMMENT "Running Standard Strumok Tests..."
        USES_TERMINAL
)


add_executable(strumok_attack 
        test-attack.cpp
)
target_include_directories(strumok_attack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(strumok_attack PRIVATE strumok_lib gtest_main)
gtest_discover_tests(strumok_attack)

add_custom_target(run_attack
        COMMAND strumok_attack
        DEPENDS strumok_attack
        COMMENT "Running Attack Simulation..."
        USES_TERMINAL
)