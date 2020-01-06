project(mivney4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(rank_test avl_test_2.cpp)
add_executable(mivney4 main.cpp DoubleLinkedList.h rank_avl_tree.h
        hash_table.h)
add_executable(hash_test hash_table_tests.cpp)
