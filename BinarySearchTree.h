#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include "BinaryNode.h"


template<class T>
class BinarySearchTree
{
public:
    BinarySearchTree( );
    void insert( T value );
//    void remove( T value );
    void print();
    int getNumElements() const;
    T getSum() const;

    T getMax() const;
    T getMin() const;

    int stepsTo( T value ) const;

    template<class T2>
    T2 forEach(T2 f ) const
    {
        forEachRecursive( m_root->getLeftChild(), f );
        return f;
    }

private:
    void insert( BinaryNode<T>* root, T value );
//    void remove( BinaryNode<T>* root, T value );
    BinaryNode<T>* m_root;

    template<class T2>
    void forEachRecursive(BinaryNode<T> *node, T2& f ) const
    {
        if( node == nullptr ) return;
        forEachRecursive( node->getLeftChild(), f );
        f( node );
        forEachRecursive( node->getRightChild(), f );
    }

};

#endif // BINARYSEARCHTREE_H
