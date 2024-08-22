cmake_minimum_required(VERSION 3.5.0)
project(CFD VERSION 0.1.0 LANGUAGES C)

include_directories(include)
include_directories(raylib/include)

set(HEADERS 
    include/Grid1D.h
    include/PDESolver.h
    include/Assets.h
    include/Visualise.h)

set(SOURCES
    src/Grid1D.c
    src/PDESolver.c
    src/Assets.c
    src/Visualise.c)

link_directories(raylib-5.0_linux_amd64/lib)

add_compile_options(-Wall -Werror)

add_executable(CFD src/main.c ${SOURCES} ${HEADERS})

target_link_libraries(CFD m raylib)


