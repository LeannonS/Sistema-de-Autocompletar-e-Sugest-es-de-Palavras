#include <bits/stdc++.h>

#ifndef AVLTREE_HPP
#define AVLTREE_HPP

using namespace std;

class AVLTree
{
  private:
    pair<string, int> data;
    AVLTree* left;
    AVLTree* right;
    int weight;

  public:
    AVLTree();

    void destroyAVLTree(AVLTree *t);

    void insertAVLTree(AVLTree **t, const pair<string, int>& word);

    int getWeight(AVLTree **t);
    int getMaxWeight(int left, int right);

    void rotacaoSimplesDireita(AVLTree **t);
    void rotacaoSimplesEsquerda(AVLTree **t);
    void rotacaoDuplaDireita(AVLTree **t);
    void rotacaoDuplaEsquerda(AVLTree **t);

    void printAVLTreePosOrdem(AVLTree *t, ofstream& outputFile);
    void printAVLTreePreOrdem(AVLTree *t, ofstream& outputFile);
    void printAVLTreeInOrdem(AVLTree *t, ofstream& outputFile);
    void printAVLTree(AVLTree *t, ofstream& outputFile);
};

#endif