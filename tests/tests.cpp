#include <gtest/gtest.h>

#include "DataStructures/test_node.cpp"
#include "DataStructures/test_list.cpp"
#include "DataStructures/test_BST.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
