#include "BinaryNode.h"

template<class T>
BinaryNode<T>::BinaryNode( T value )
{
    m_data = value;
    for( unsigned int i = 0; i < m_nChildren; ++i )
    {
        m_children[i] = nullptr;
    }
    m_isRoot = false;
}

template<class T>
T BinaryNode<T>::getValue() const
{
    return m_data;
}

template<class T>
void BinaryNode<T>::setLeftChild( BinaryNode<T>* left )
{
    m_children[LEFT] = left;
}

template<class T>
void BinaryNode<T>::setRightChild( BinaryNode<T>* right )
{
    m_children[RIGHT] = right;
}

template<class T>
BinaryNode<T>* BinaryNode<T>::getLeftChild()
{
    return m_children[LEFT];
}

template<class T>
BinaryNode<T> *BinaryNode<T>::getRightChild()
{
    return m_children[RIGHT];
}

template class BinaryNode<int>;

