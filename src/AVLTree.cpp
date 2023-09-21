#include "AVLTree.hpp"

AVLTree::AVLTree()
{
}

void AVLTree::destroyAVLTree(AVLTree *t)
{
  if (t != nullptr)
  {
    destroyAVLTree(t->left);
    destroyAVLTree(t->right);
    delete t;
  }
}

void AVLTree::insertAVLTree(AVLTree **t, const pair<string, int>& word)
{
  if(*t == nullptr)
  {
    *t = new AVLTree;
    (*t)->left   = nullptr; 
    (*t)->right  = nullptr; 
    (*t)->weight = 0;
    (*t)->data   = word; 
  }
  else
  {
    if(word.second <= (*t)->data.second)
    {
      insertAVLTree(&(*t)->left, word);
      if ((getWeight(&(*t)->left) - getWeight(&(*t)->right)) == 2)
      {
      	if(word.second <= (*t)->left->data.second)
      		rotacaoSimplesDireita(t);
      	else
      		rotacaoDuplaDireita(t);
      }
    }
    
    else
    {
      insertAVLTree(&(*t)->right, word);
      if ((getWeight(&(*t)->right) - getWeight(&(*t)->left)) == 2)
      {
      	if(word.second > (*t)->right->data.second)
      		rotacaoSimplesEsquerda(t);
      	else
      		rotacaoDuplaEsquerda(t);
      }
    }
  }
  (*t)->weight = getMaxWeight(getWeight(&(*t)->left), getWeight(&(*t)->right)) + 1;
}

int AVLTree::getWeight(AVLTree **t)
{
  if(*t == nullptr)
		return -1;
	return (*t)->weight;
}

int AVLTree::getMaxWeight(int left, int right)
{
  if(left > right)
		return left;
	return right;
}

void AVLTree::rotacaoSimplesDireita(AVLTree **t)
{
	AVLTree *aux;
	aux = (*t)->left;
	(*t)->left = aux->right;
	aux->right = (*t);
	(*t)->weight = getMaxWeight(getWeight(&(*t)->left), getWeight(&(*t)->right)) + 1;
	aux->weight  = getMaxWeight(getWeight(&aux->left), (*t)->weight) + 1;
	(*t) = aux;
}

void AVLTree::rotacaoSimplesEsquerda(AVLTree **t)
{
	AVLTree *aux;
	aux = (*t)->right;
	(*t)->right = aux->left;
	aux->left = (*t);
	(*t)->weight = getMaxWeight(getWeight(&(*t)->left), getWeight(&(*t)->right)) + 1;
	aux->weight  = getMaxWeight(getWeight(&aux->left), (*t)->weight) + 1;
	(*t) = aux;
}

void AVLTree::rotacaoDuplaDireita(AVLTree **t)
{
	rotacaoSimplesEsquerda(&(*t)->left);
	rotacaoSimplesDireita(t);
}

void AVLTree::rotacaoDuplaEsquerda(AVLTree **t)
{
	rotacaoSimplesDireita(&(*t)->right);
	rotacaoSimplesEsquerda(t);
}

void AVLTree::printAVLTreePosOrdem(AVLTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    printAVLTreePosOrdem(t->left, outputFile); 
    printAVLTreePosOrdem(t->right, outputFile); 
    outputFile << t->data.first << " : " << t->data.second << " / ";
  }
}

void AVLTree::printAVLTreePreOrdem(AVLTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    outputFile << t->data.first << " : " << t->data.second << " / ";
    printAVLTreePreOrdem(t->left, outputFile);
    printAVLTreePreOrdem(t->right, outputFile);
  }
}

void AVLTree::printAVLTreeInOrdem(AVLTree *t, ofstream& outputFile)
{
  if(!(t == nullptr))
  {
    printAVLTreeInOrdem(t->left, outputFile);
    outputFile << t->data.first << " : " << t->data.second << " / ";
    printAVLTreeInOrdem(t->right, outputFile);
  }
}

void AVLTree::printAVLTree(AVLTree *t, ofstream& outputFile)
{
  outputFile << "]\n\nAVL Tree (Pós-Ordem):\n[";
  printAVLTreePosOrdem(t, outputFile); 

  outputFile << "]\n\nAVL Tree (Pré-Ordem):\n[";
  printAVLTreePreOrdem(t, outputFile);

  outputFile << "]\n\nAVL Tree (In-Ordem):\n[";
  printAVLTreeInOrdem(t, outputFile);
}