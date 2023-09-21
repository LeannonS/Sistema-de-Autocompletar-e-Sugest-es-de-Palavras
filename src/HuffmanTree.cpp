#include "HuffmanTree.hpp"

void HuffmanTree::createHuffmanTree(HuffmanTree*& t, vector<pair<wstring, int>>& data)
{
  priority_queue<HuffmanTree*, vector<HuffmanTree*>, comp> pq;

  for (const pair<wstring, int>& word : data)
  {
    HuffmanTree* aux = new HuffmanTree;

    pair<wstring, int> data;

    data.second = word.second;
    data.first = word.first;

    aux->prob = word.second;

    aux->data = data;

    aux->left = nullptr;
    aux->right = nullptr;

    pq.push(aux);
  }

  while (pq.size() > 1)
  {
    HuffmanTree* left = pq.top();
    pq.pop();

    HuffmanTree* right = pq.top();
    pq.pop();

    HuffmanTree* aux = new HuffmanTree;

    aux->prob = left->prob + right->prob;
    aux->left = left;
    aux->right = right;

    pq.push(aux);
  }

  t = pq.top();
}

void HuffmanTree::printHuffmanTreePosOrdem(HuffmanTree* t, ofstream& outputFile, string code)
{
  wstring_convert<codecvt_utf8<wchar_t>> converter;

  if (t == nullptr)
  {
    return;
  }

  printHuffmanTreePosOrdem(t->left, outputFile, code + "0");
  printHuffmanTreePosOrdem(t->right, outputFile, code + "1");

  if (!t->data.first.empty())
  {
    outputFile << converter.to_bytes(t->data.first) << " : " << t->data.second << " : " << code << " / ";
  }
}

void HuffmanTree::printHuffmanTreePreOrdem(HuffmanTree* t, ofstream& outputFile, string code)
{
  wstring_convert<codecvt_utf8<wchar_t>> converter;
  
  if (t == nullptr)
  {
    return;
  }

  if (!t->data.first.empty())
  {
    outputFile << converter.to_bytes(t->data.first) << " : " << t->data.second << " : " << code << " / ";
  }

  printHuffmanTreePreOrdem(t->left, outputFile, code + "0");
  printHuffmanTreePreOrdem(t->right, outputFile, code + "1");
}

void HuffmanTree::printHuffmanTreeInOrdem(HuffmanTree* t, ofstream& outputFile, string code)
{
  wstring_convert<codecvt_utf8<wchar_t>> converter;

  if (t == nullptr)
  {
    return;
  }

  printHuffmanTreeInOrdem(t->left, outputFile, code + "0");

  if (!t->data.first.empty())
  {
    outputFile << converter.to_bytes(t->data.first) << " : " << t->data.second << " : " << code << " / ";
  }

  printHuffmanTreeInOrdem(t->right, outputFile, code + "1");
}


void HuffmanTree::destroyHuffmanTree(HuffmanTree* t)
{
  if (t == nullptr)
  {
    return;
  }

  destroyHuffmanTree(t->left);
  destroyHuffmanTree(t->right);

  delete t;
}

void HuffmanTree::printHuffmanTree(HuffmanTree* t, ofstream& outputFile)
{
  outputFile << "]\n\nHuffman Tree (Pós-Ordem):\n[";
  printHuffmanTreePosOrdem(t, outputFile, ""); 

  outputFile << "]\n\nHuffman Tree (Pré-Ordem):\n[";
  printHuffmanTreePreOrdem(t, outputFile, "");

  outputFile << "]\n\nHuffman Tree (In-Ordem):\n[";
  printHuffmanTreeInOrdem(t, outputFile, "");
  outputFile << "]\n-----------------------------------------------------------------------------\n\n";
}