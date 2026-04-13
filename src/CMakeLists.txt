file(GLOB STRUMOK "Strumok/*.cpp")

add_library(strumok_lib
        ${STRUMOK}
        include/strumok_tables.c
)

target_include_directories(strumok_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Strumok
)

add_executable(strumok_benchmark
        benchmark/main.cpp
)
target_link_libraries(strumok_benchmark PRIVATE strumok_lib)

add_custom_target(run_benchmark
        COMMAND strumok_benchmark
        DEPENDS strumok_benchmark
        COMMENT "Running Strumok Benchmark..."
        USES_TERMINAL 
)