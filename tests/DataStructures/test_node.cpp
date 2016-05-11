#include "../../Node.h"
TEST(NodeTests, Create)
{
    Node<int>* n1 = new Node<int>();
    EXPECT_EQ( n1->getNext(), nullptr);

    Node<int>* n2 = new Node<int>( 1 );
    EXPECT_EQ( n2->getValue(), 1 );
}

TEST(NodeTests, set)
{
    Node<int>* n1 = new Node<int>();
    n1->setValue( 1337 );
    EXPECT_EQ( n1->getValue(), 1337 );

    Node<int>* n2 = new Node<int>( 1 );
    n1->setNext( n2 );
    EXPECT_EQ( n1->getNext(), n2 );
}
