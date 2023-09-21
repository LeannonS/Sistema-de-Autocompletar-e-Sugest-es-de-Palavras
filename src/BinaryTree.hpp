#include <bits/stdc++.h>

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

using namespace std;

class BinaryTree
{
  private:
    pair<string, int> data;
    BinaryTree* left;
    BinaryTree* right;

  public:
    BinaryTree();

    void insertBinaryTree(BinaryTree **t, const pair<string, int>& word);
    void printBinaryTreePosOrdem(BinaryTree *t, ofstream& outputFile);
    void printBinaryTreePreOrdem(BinaryTree *t, ofstream& outputFile);
    void printBinaryTreeInOrdem(BinaryTree *t, ofstream& outputFile);
    void printBinaryTree(BinaryTree *t, ofstream& outputFile);
    void destroyBinaryTree(BinaryTree *t);
};

#endif