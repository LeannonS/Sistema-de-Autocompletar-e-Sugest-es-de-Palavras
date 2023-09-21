#include "BinaryTree.hpp"

BinaryTree::BinaryTree()
{
}

void BinaryTree::insertBinaryTree(BinaryTree **t, const pair<string, int>& word)
{
  if (*t == nullptr)
  {
    *t = new BinaryTree;
    (*t)->data = word;
    (*t)->left = nullptr;
    (*t)->right = nullptr;
  }
  else
  {
    BinaryTree *aux = *t;
    
    while(aux != nullptr)
    {
      if(word.second <= aux->data.second)
      {
        if (aux->left == nullptr)
        {
          aux->left = new BinaryTree;
          aux = aux->left;
          aux->data = word;
          aux->left = nullptr;
          aux->right = nullptr;
        }
        aux = aux->left;
      }
      else
      {
        if (aux->right == nullptr)
        {
          aux->right = new BinaryTree;
          aux = aux->right;
          aux->data = word;
          aux->left = nullptr;
          aux->right = nullptr;
        }
        aux = aux->right;
      }
    }
  }
}

void BinaryTree::printBinaryTreePosOrdem(BinaryTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    printBinaryTreePosOrdem(t->left, outputFile); 
    printBinaryTreePosOrdem(t->right, outputFile); 
    outputFile << t->data.first << " : " << t->data.second << " / ";
  }
}

void BinaryTree::printBinaryTreePreOrdem(BinaryTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    outputFile << t->data.first << " : " << t->data.second << " / ";
    printBinaryTreePreOrdem(t->left, outputFile);
    printBinaryTreePreOrdem(t->right, outputFile);
  }
}

void BinaryTree::printBinaryTreeInOrdem(BinaryTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    printBinaryTreeInOrdem(t->left, outputFile);
    outputFile << t->data.first << " : " << t->data.second << " / ";
    printBinaryTreeInOrdem(t->right, outputFile);
  }
}

void BinaryTree::printBinaryTree(BinaryTree *t, ofstream& outputFile)
{
  outputFile << "Binary Tree (Pós-Ordem):\n[";
  printBinaryTreePosOrdem(t, outputFile); 

  outputFile << "]\n\nBinary Tree (Pré-Ordem):\n[";
  printBinaryTreePreOrdem(t, outputFile);

  outputFile << "]\n\nBinary Tree (In-Ordem):\n[";
  printBinaryTreeInOrdem(t, outputFile);
}

void BinaryTree::destroyBinaryTree(BinaryTree *t)
{
  if (t == nullptr)
  {
    return;
  }
  
  destroyBinaryTree(t->left);
  destroyBinaryTree(t->right);
  
  delete t;
}

