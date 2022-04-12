#ifndef LIST_H
#define LIST_H

#include "node.hpp"



template <class DATATYPE>
class List : public Node<DATATYPE>
{
    private: 
    Node<DATATYPE> *ptrHead;

    public:
    List(void)
    {
        ptrHead = nullptr;
    }


    ~List()
    {
      while(ptrHead != nullptr)
      {
          Node<DATATYPE> *current = ptrHead;
          ptrHead = ptrHead->ptrNext;
          delete current;
      }
    }


    void addNode(DATATYPE *newData)
    {
        Node<DATATYPE> *newNode = new Node<DATATYPE>(newData);
        if(this->ptrHead != nullptr)
        {
            newNode->ptrNext = this->ptrHead;
        }
    
        this->ptrHead = newNode;

    }



    void printList(void)
    {
        Node<Data> *current = this->ptrHead;
            while(current != nullptr)
            {
                current->nodeData->printCommand();
                current->nodeData->printDescription();

                current = current->ptrNext;
            }
    }


     Node<DATATYPE>* returnHead(void)
  {
      return this->ptrHead;
  }



};









#endif