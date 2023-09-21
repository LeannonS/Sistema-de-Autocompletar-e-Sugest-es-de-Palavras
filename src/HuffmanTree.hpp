#include <bits/stdc++.h>

#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

using namespace std;

class HuffmanTree
{
  private:
    pair<wstring, int> data;
    int prob;
    HuffmanTree* left;
    HuffmanTree* right;

    struct comp
    {
      constexpr bool operator()(HuffmanTree* const& a, HuffmanTree* const& b) const noexcept
      {
        return a->prob >= b->prob;
      }
    };

  public:
    void createHuffmanTree(HuffmanTree*& t, vector<pair<wstring, int>>& data);
    void printHuffmanTreePosOrdem(HuffmanTree* t, ofstream& outputFile, string code);
    void printHuffmanTreePreOrdem(HuffmanTree* t, ofstream& outputFile, string code);
    void printHuffmanTreeInOrdem(HuffmanTree* t, ofstream& outputFile, string code);
    void printHuffmanTree(HuffmanTree* t, ofstream& outputFile);
    void destroyHuffmanTree(HuffmanTree* t);
};

#endif