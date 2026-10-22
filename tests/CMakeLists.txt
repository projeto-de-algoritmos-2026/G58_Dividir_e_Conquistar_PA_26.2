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
)
target_link_libraries(rhyme_tests PRIVATE rhyme_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(rhyme_tests)
