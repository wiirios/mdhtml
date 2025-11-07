cmake_minimum_required(VERSION 3.10)
project(mdhtml C)

set(SOURCES
    src/main.c
    src/reader.c
)

add_executable(mdhtml ${SOURCES})

target_include_directories(mdhtml PRIVATE src)