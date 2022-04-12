#include <cstdlib>
#include <iostream>

#include "AVLTree.h"
#include <vector>
#include <random>
#include <algorithm>

int main(void)
{
    srand(time(NULL));

    auto rng = std::default_random_engine{};
  
    AVLTree<int> *ascendingTree = new AVLTree<int>();
    AVLTree<int> *descendingTree = new AVLTree<int>();
    AVLTree<int> *randomTree = new AVLTree<int>(); 

    int vect[50];
    int k = 0;
    for (int i = 0; i <= 100; i++)
    {
        int j = 100 - i;
        if (i % 2 != 0)
        {
            ascendingTree->insert(i);   
            descendingTree->insert(j);
            vect[k] = i;
            k++;
        }

    }
    
    std::shuffle(std::begin(vect), std::end(vect), rng);
    for (int i = 0; i < 50; i++)
    {
        randomTree->insert(vect[i]);
    }
    
   std::cout << "Height of Ascending Tree: " << ascendingTree->height() << std::endl;
   std::cout << "Height of Descending Tree: " << descendingTree->height() << std::endl;
   std::cout << "Height of Random Tree: " << randomTree->height() << std::endl;


   std::cout << "AscendingTree Validation: " << ascendingTree->validate() << std::endl;
   std::cout << "DescendingTree Validation: " << descendingTree->validate() << std::endl;
   std::cout << "RandomTree Validation: " << randomTree->validate() << std::endl;


    for (int i = 0; i < 101; i++)
    {
        if (i % 2 == 0 && ascendingTree->contains(i))
        {
            std::cout << "My AVL tree Implementation is wrong" << std::endl;
        }
         if (i % 2 == 0 && descendingTree->contains(i))
        {
            std::cout << "My AVL tree Implementation is wrong" << std::endl;
        }
         if (i % 2 == 0 && randomTree->contains(i))
        {
            std::cout << "My AVL tree Implementation is wrong" << std::endl;
        }
    }

    
    
    

    return 0;
}