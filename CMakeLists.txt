cmake_minimum_required(VERSION 3.5.0)
project(CFD VERSION 0.1.0 LANGUAGES C)

include_directories(include)
include_directories(raylib/include)

set(HEADERS 
    include/Grid1D.h
    include/PDESolver.h
    include/Assets.h
    include/Visualise.h
    include/Matrix2D.h
    include/Grid2D.h)

set(TEST_HEADERS 
    include/Grid1D.h
    include/PDESolver.h
    include/Matrix2D.h
    include/Grid2D.h)

set(SOURCES
    src/Grid1D.c
    src/PDESolver.c
    src/Assets.c
    src/Visualise.c
    src/Matrix2D.c
    src/Grid2D.c)

set(TEST_SOURCES
    src/Grid1D.c
    src/PDESolver.c
    src/Matrix2D.c
    src/Grid2D.c)

link_directories(raylib-5.0_linux_amd64/lib)

add_compile_options(-Wall -Werror)

add_executable(CFD src/main.c ${SOURCES} ${HEADERS})
add_executable(Test src/test.c ${TEST_SOURCES} ${TEST_HEADERS})

target_link_libraries(CFD m raylib)


