#include "BinarySearchTree.h"
#include <stdio.h>
#include <assert.h>     /* assert */

template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
    m_root = new BinaryNode<T>(-1);
    m_root->setToRoot();
}

template<class T>
void BinarySearchTree<T>::insert( T value )
{

   //Find where to add it
   if( m_root->getLeftChild() == nullptr ) //Root only uses left ptr
   {
        BinaryNode<T>* newNode = new BinaryNode<T>( value );
        m_root->setLeftChild( newNode );
   }
   else
   {
       insert( m_root->getLeftChild(), value );
   }
}

template<class T>
void BinarySearchTree<T>::insert( BinaryNode<T>* root, T value )
{
    if( value < root->getValue() )
    {
        BinaryNode<T>* left = root->getLeftChild();
        if( left == nullptr )
        {
            BinaryNode<T>* newNode = new BinaryNode<T>( value );
            root->setLeftChild( newNode );
        }
        else
        {
            assert( left->getValue() <= root->getValue() );
            insert( left, value );
        }
    }
    else if( value > root->getValue() ) //root->getValue() > value
    {
        BinaryNode<T>* right = root->getRightChild();
        if( right == nullptr )
        {
            BinaryNode<T>* newNode = new BinaryNode<T>( value );
            root->setRightChild( newNode );
        }
        else
        {
            assert( right->getValue() > root->getValue() );
            insert( right, value );
        }
    }
    else
    {
        //Value to be inserted already exists => do nothing because only unique values are allowed
    }
}


//The number of nodes that have been steped over before finding a node with the given value as value
template<class T>
int BinarySearchTree<T>::stepsTo( T value ) const
{
    struct distanceMeasurer
    {
        distanceMeasurer(T v): isFound(false), steps(0), value(v) { }
        //void operator()( BinaryNode<T>* n ) { wxMessageOutput::Get()->Printf(" %d, ", n->getValue() ); }
        void operator()( BinaryNode<T>* n )
        {
            if( n->getValue() == value )
            {
                isFound = true;
            }

            if( !isFound )
            {
                ++steps;
            }
        }
        bool isFound;
        int steps;
        T value;
    };

    distanceMeasurer result = forEach( distanceMeasurer( value ) );
    if( result.isFound )
    {
        return result.steps;
    }
    else
    {
        return -1;
    }
}

/*
template<class T>
void BinarySearchTree<T>::remove( T value )
{
    BinaryNode<T>* ptr = m_root;
    if( ptr->getLeftChild() != nullptr )
    {
        remove( ptr, value );
    }
}
*/

/*
template<class T>
void BinarySearchTree<T>::remove( BinaryNode<T>* root, T value )
{
    if( root == nullptr ) return;
    //Find node to remove, n1 and its parent p1
    //Find node to replace with, n2 and its parent p2
    //Change p2 to point to null instead of n2
    //Change p1 to point to n2 instead of n1
    //Change n2 to point to same children as n1

    BinaryNode<T>* n1,p1,n2,p2;
}
*/

template<class T>
void BinarySearchTree<T>::print()
{
    struct Printer
    {
        Printer(){ }
        //void operator()( BinaryNode<T>* n ) { wxMessageOutput::Get()->Printf(" %d, ", n->getValue() ); }
        void operator()( BinaryNode<T>* n ) { std::cout << " " << n->getValue() << ", "; }
    };

    forEach( Printer() );
}

template<class T>
int BinarySearchTree<T>::getNumElements() const
{
    struct ElementCounter
    {
        ElementCounter(): num(0) { }
        void operator()( BinaryNode<T>* ) { ++num; }
        int num;
    };

    ElementCounter result = forEach( ElementCounter() );
    return result.num;
}

template<class T>
T BinarySearchTree<T>::getSum() const
{
    struct Summer
    {
        Summer(): sum(0) { }
        void operator()( BinaryNode<T>* n ) { sum += n->getValue(); }
        T sum;
    };

    Summer sum = forEach( Summer() );
    return sum.sum;
}

template<class T>
T BinarySearchTree<T>::getMax() const
{
    BinaryNode<T>* node = m_root->getLeftChild();
    if( node == nullptr ) return -1;

    while( node->getRightChild() != nullptr )
    {
        node = node->getRightChild();
    }
    return node->getValue();
}

template<class T>
T BinarySearchTree<T>::getMin() const
{
    BinaryNode<T>* node = m_root->getLeftChild();
    if( node == nullptr ) return -1;

    while( node->getLeftChild() != nullptr )
    {
        node = node->getLeftChild();
    }
    return node->getValue();
}

/*
template<class T>
template<class UnaryFunction>
UnaryFunction BinarySearchTree<T>::forEach( UnaryFunction f ) const
{
    forEachRecursive( m_root, f );
    return f;
}



template<class T>
template<class UnaryFunction>
void BinarySearchTree<T>::forEachRecursive( BinaryNode<T>* node, UnaryFunction& f ) const
{
    if( node == nullptr ) return;
    forEachRecursive( node->getLeftChild(), f );
    f( node->getValue() );
    forEachRecursive( node->getRightChild(), f );
}
*/
/*
template<class T>
template<class T2>
void BinarySearchTree<T>::forEach( T2& sum ) const
{
    forEachRecursive( m_root->getLeftChild(), sum );
}
*/

/*
template<class T>
template<class T2>
void BinarySearchTree<T>::forEachRecursive( BinaryNode<T>* node, T2& sum ) const
{
    if( node == nullptr ) return;
    forEachRecursive( node->getLeftChild(), sum );
    sum += node->getValue();
    forEachRecursive( node->getRightChild(), sum );
}
*/
template class BinarySearchTree<int>;

