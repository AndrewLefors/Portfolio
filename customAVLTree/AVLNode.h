#ifndef AVLNODE_H
#define AVLNODE_H


template <class DATA>
struct Node
{
    DATA data;
    Node<DATA> *left;
    Node<DATA> *right;
    int height;


    Node(void)
    {
        data = 0;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
    Node(DATA newData)
    {
        data = newData;
        left = nullptr;
        right = nullptr;
        height = 0;
    }


    ~Node()
    {
        delete this;
    }
};










#endif