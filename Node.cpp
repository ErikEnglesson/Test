#include "Node.h"

template<class T>
Node<T>::Node()
{
    next = nullptr;
}

template<class T>
Node<T>::Node( T value )
{
    data = value;
    next = nullptr;
}

template<class T>
void Node<T>::setValue( T value )
{
    data = value;
}

template<class T>
T Node<T>::getValue() const
{
    return data;
}

template<class T>
Node<T>* Node<T>::getNext()
{
    return next;
}

template<class T>
void Node<T>::setNext( Node<T> * nextPtr )
{
    next = nextPtr;
}

template class Node<int>;

