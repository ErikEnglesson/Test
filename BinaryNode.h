#ifndef BINARYNODE_H
#define BINARYNODE_H

template<class T>
class BinaryNode
{
    //friend class BinarySearchTree;
    enum { LEFT=0, RIGHT=1 };
public:
    BinaryNode( T value );
    T getValue() const;

    BinaryNode<T> *getLeftChild();
    BinaryNode<T>* getRightChild();
    void setLeftChild( BinaryNode<T>* left );
    void setRightChild( BinaryNode<T>* right );
    void setToRoot() { m_isRoot = true; }
private:
    T m_data;
    static const unsigned int m_nChildren = 2;
    BinaryNode* m_children[m_nChildren]; // 0 = left, 1 = right
    bool m_isRoot;
};

#endif // BINARYNODE_H
