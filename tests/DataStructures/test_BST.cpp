#include "../../BinarySearchTree.h"
#include <gtest/gtest.h>

TEST(BST, Insert)
{
    BinarySearchTree<int> BST;

    BST.insert(8);
    BST.insert(3);
    BST.insert(10);
    BST.insert(1);
    BST.insert(6);
    BST.insert(4);
    BST.insert(7);
    BST.insert(14);
    BST.insert(13);

    //BUILDS THE FOLLOWING TREE:
    /*
     *
          8
        /  \
       3    10
      /\      \
     1 6      14
      /\     /
     4  7   13
    *
    */


    BST.print();
    std::cout << std::endl;

    EXPECT_EQ( BST.getNumElements(), 9 );

    //Add already existing value which should not increase the number of elements
    BST.insert(13);
    EXPECT_EQ( BST.getNumElements(), 9 );

    EXPECT_EQ( BST.getSum(), 66 );
    EXPECT_EQ( BST.getMax(), 14 );
    EXPECT_EQ( BST.getMin(), 1 );



    //Steps to get to 14
    EXPECT_EQ( BST.stepsTo( 14 ), BST.getNumElements()-1 );
    EXPECT_EQ( BST.stepsTo( 7 ), 4 );
    EXPECT_EQ( BST.stepsTo( 10 ), 6 );


}
