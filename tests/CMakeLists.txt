include(FetchContent)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(googletest)

# Acrescente aqui cada arquivo de teste novo (test_graph.cpp, test_kruskal.cpp, ...)
add_executable(rhyme_tests
        test_unionfind.cpp
        test_delaunaygraph.cpp
        test_structs.cpp
        test_kruskal.cpp
        test_quadedge.cpp
        test_predicates.cpp
        test_delaunay.cpp
        test_rhymeindex.cpp
        test_translator.cpp
        test_cmudictionary.cpp
)

target_compile_definitions(rhyme_tests PRIVATE FIXTURES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/fixtures")


target_link_libraries(rhyme_tests PRIVATE rhyme_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(rhyme_tests)
