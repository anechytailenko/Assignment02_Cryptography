file(GLOB STRUMOK "Strumok/*.cpp")

add_library(strumok_lib
        ${STRUMOK}
        include/strumok_tables.c
)

target_include_directories(strumok_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Strumok
)