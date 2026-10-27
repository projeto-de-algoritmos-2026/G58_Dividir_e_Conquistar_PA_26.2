cmake_minimum_required(VERSION 3.20)
project(G58_Dividir_e_Conquistar_PA_26_2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(rhyme_core STATIC
        modelo/adaptadores/AcousticTranslator.cpp
        modelo/adaptadores/CmuDictionary.cpp
        modelo/geometria/DelaunayGraph.cpp
        modelo/geometria/DivideConquerDelaunay.cpp
        modelo/geometria/KruskalClusterer.cpp
        modelo/geometria/UnionFind.cpp
        modelo/nucleo/RhymeEngine.cpp
        modelo/nucleo/RhymeIndex.cpp
        modelo/terminal/TerminalUI.cpp
        modelo/geometria/QuadEdge.cpp
        modelo/geometria/predicates.c
        modelo/geometria/predicates.h
)

target_include_directories(rhyme_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(rhyme_core PRIVATE -Wall -Wextra)
endif ()


add_executable(rhyme modelo/terminal/main.cpp)
target_link_libraries(rhyme PRIVATE rhyme_core)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bench/bench_delaunay.cpp)
    add_executable(rhyme_bench bench/bench_delaunay.cpp)
    target_link_libraries(rhyme_bench PRIVATE rhyme_core)
endif ()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    enable_testing()
    add_subdirectory(tests)
endif ()

set_source_files_properties(modelo/geometria/predicates.c PROPERTIES COMPILE_OPTIONS "-w;-fno-sanitize=address")
