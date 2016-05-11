#ifndef LIST_H
#define LIST_H

#include "Node.h"

template<class T>
class List
{
public:
    List()
    {
       m_size = 0;
    }

    void add( T value );
    void remove( T value );
    void print();

    unsigned int size() const { return m_size; }

private:
    Node<T> m_root;
    unsigned int m_size;

};

#endif // LIST_H
