#include "List.h"
#include <stdio.h>

template<class T>
void List<T>::add(T value)
{
    Node<T> * ptr = &m_root;
    while( ptr->getNext() != nullptr )
    {
        ptr = ptr->getNext();
    }
    Node<T> * newEntry = new Node<T>( value );
    ptr->setNext( newEntry );
    m_size++;
}

template<class T>
void List<T>::remove(T value)
{
    Node<T>* ptr = &m_root;
    while( ptr->getNext() != nullptr )
    {
        if( ptr->getNext()->getValue() == value )
        {
            //Remove
            Node<T> * r = ptr->getNext();
            ptr->setNext( r->getNext() );
            delete r;
            m_size--;
            continue;
        }
        ptr = ptr->getNext();
    }
}

template<class T>
void List<T>::print()
{
    Node<T> * ptr = m_root.getNext();
    while( ptr != nullptr )
    {
        printf("%d, ", ptr->getValue() );
        ptr = ptr->getNext();
    }
    printf("\n");
}

template class List<int>;


