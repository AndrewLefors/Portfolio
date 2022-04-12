#ifndef AVLTREE_H
#define AVLTREE_H


#define MAXIMUM_HEIGHT_DIFFERENCE 1;
#include "AVLNode.h"

template <class DATA>
class AVLTree
{
    private:
    Node<DATA>* root;


    ////BEGIN PRIVATE API///////

	void destroyTree(Node<DATA> *rootNode)
	{
		if (!root)
		{
			return;
		}

		destroyTree(rootNode->left);
		destroyTree(rootNode->right);
		delete rootNode;
	}



void insertHelper(DATA data, Node<DATA> *&node) const
{
	if (node == nullptr)
	{
		node = new Node<DATA>(data);
	}
	else if (data < node->data)
	{
		insertHelper(data, node->left);
		if( height( node->left ) - height( node->right ) > 1 )
                    if( data < node->left->data )
                        rotateWithLeftChild( node );
                    else
                        doubleWithLeftChild( node );
	}
	else if ( node->data < data)
	{
		insertHelper(data, node->right);
		if( height( node->right ) - height( node->left ) > 1 )
                    if( node->right->data < data )
                        rotateWithRightChild( node );
                    else
                        doubleWithRightChild( node );
	}

	node->height = std::max(height(node->left), height(node->right)) + 1;
}



bool containsValueHelper(Node<DATA> *root, DATA value) 
    {
		if (!root) return false;
		if (root->data == value) 
		{
			return true;
		}
		return containsValueHelper(root->left, value) || containsValueHelper(root->right, value);

		
	}

    	
    

    /////BEGIN PUBLIC API///////
    public:

    AVLTree(Node<DATA>*node)
    {
        root = node;
    }

    AVLTree(void)
    {
        root = nullptr;
  
    }

	~AVLTree()
	{
		destroyTree(root);
	}


void balance(Node<DATA> *&node)
{
	if(node == nullptr)
    {
         return;
    }

	if(height(node->left) - height(node->right) > 1)
		{
			if (height(node->left->left) >= height(node->left->right))
			{
				rotateWithLeftChild(node);
			}
			else
			{
				doubleWithLeftChild(node);
			}

		}
		else
		{
			if(height(node->right) - height(node->left) > 1)
			{
				if (height(node->right->right) >= height(node->right->left))
				{
					rotateWithRightChild(node);

				}
				else
				{
					doubleWithRightChild(node);
				}
			}
		}
		node->height = std::max(height(node->left), height(node->right)) + 1;
    
    }

int height(Node<DATA>* root) const
        {
			return root == nullptr ? -1 : root->height;
	    }

int height() const
        {
			return this->root == nullptr ? -1 : this->root->height;
	    }


bool contains(DATA value) 
    {
		return containsValueHelper(this->root, value);
	}





 void rotateWithLeftChild(Node<DATA> * & k2 ) const
        {
            Node<DATA> *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = std::max( height( k2->left ), height( k2->right ) ) + 1;
            k1->height = std::max( height( k1->left ), k2->height ) + 1;
            k2 = k1;
        }

void rotateWithRightChild( Node<DATA> * & k1 ) const
        {
            Node<DATA> *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1->height = std::max( height( k1->left ), height( k1->right ) ) + 1;
            k2->height = std::max( height( k2->right ), k1->height ) + 1;
            k1 = k2;
        }

void doubleWithLeftChild(Node<DATA>* & k3) const
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

void doubleWithRightChild(Node<DATA> *& k1) const 
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}


void insert(DATA &data)
{
	insertHelper(data, root);
}


int validate()
{
	if (height(this->root->left) - height(this->root->right) > 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

};








#endif