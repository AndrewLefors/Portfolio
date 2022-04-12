#ifndef NODE_H
#define NODE_H

template <class DATATYPE>
class Node : private DATATYPE
{
    public: 
    DATATYPE *nodeData;
    Node<DATATYPE> *ptrNext;

    Node(void)
    {
        ptrNext = nullptr;
    }

    Node(DATATYPE *Data)
    {   
        nodeData = Data; 
        ptrNext = nullptr;
    }

    ~Node()
    {
        
    }

    

};












#endif