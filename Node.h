#ifndef NODE_H
#define NODE_H

template<class T>
class Node
{
public:
    Node();

    Node(T value );

    T getValue() const;

    void setValue( T value );

    Node<T>* getNext();

    void setNext(Node<T> *nextPtr );

private:
    T data;
    Node* next;
};

#endif // NODE_H
