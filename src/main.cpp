#include <bits/stdc++.h>
#include "Utils.hpp"
#include "BinaryTree.hpp"
#include "AVLTree.hpp"
#include "HuffmanTree.hpp"

using namespace std;

int main()
{
  setlocale(LC_ALL, "pt_BR.UTF-8");
  // Cria um objeto de localização com conversão UTF-8 para wide characters
  locale loc(locale(), new codecvt_utf8<wchar_t>);
  
  int k = 20;
  int numFiles = 6;
  Utils u;
  unordered_set<wstring> input = u.getInput(loc); // Palavras a serem removidas do texto
  vector<vector<pair<wstring, int>>> minHeap;
  vector<unordered_map<wstring, int>> frequenceMap;
  vector<unordered_map<wstring, int>> auxMap; // Variavel contendo um map de cada minHeap
  vector<pair<wstring, int>> proxTopK; // Elemento top K + 1 do texto
  wstring_convert<codecvt_utf8<wchar_t>> converter;
  BinaryTree t;
  AVLTree AVLt;
  HuffmanTree Ht;

  u.makeFrequenciesMaps(loc, numFiles, frequenceMap); // Função para salvar mapas de frequencia para cada texto na variável frequenceMap.
  u.makeHeaps(k, numFiles, frequenceMap, minHeap, proxTopK); // Função para salvar heap minimo e o elementop top k+1 para cada texto nas variáveis minHeap e proxTopK.

  for(int i = 0; i < numFiles; i++)
  {
    unordered_map <wstring, int> dataMap;
    
    for (auto j = 0u; j < minHeap[i].size(); j++)
    {
      dataMap[minHeap[i][j].first] = j;
    }
    auxMap.push_back(dataMap);
  }

  ofstream File("output.txt", ios::out | ios::trunc);

  if (!File) 
  {
    cerr << "Erro ao abrir o arquivo novamente." << endl;
    return 1;
  }
  
  for(auto aux: input)
  {
    for(int i = 0; i < numFiles; i++)
    {
      BinaryTree *raiz = nullptr;
      AVLTree *AVLRaiz = nullptr;
      HuffmanTree *HuffmanRaiz = nullptr;
      
      if(frequenceMap[i].find(aux) == frequenceMap[i].end())
      {
        File << converter.to_bytes(aux) << endl << endl << "input" << i+1 << endl << endl;
        File << "A palavra não está contida no texto!\n";
        File << "-----------------------------------------------------------------------------\n\n";
      }
      else
      {
        if(auxMap[i].find(aux) != auxMap[i].end())
        {
          vector<pair<wstring, int>> auxMinHeap = minHeap[i];
          u.swapMinHeap(auxMinHeap, auxMap[i][aux], proxTopK, i);
          
          File << converter.to_bytes(aux) << endl << endl << "input" << i+1 << endl << endl;
          Ht.createHuffmanTree(HuffmanRaiz, auxMinHeap);
          for(auto w: auxMinHeap)
          {
            t.insertBinaryTree(&raiz, make_pair(converter.to_bytes(w.first), w.second));
            AVLt.insertAVLTree(&AVLRaiz, make_pair(converter.to_bytes(w.first), w.second));
          }
          t.printBinaryTree(raiz, File);
          t.destroyBinaryTree(raiz);

          AVLt.printAVLTree(AVLRaiz, File);
          AVLt.destroyAVLTree(AVLRaiz);

          Ht.printHuffmanTree(HuffmanRaiz, File);
          Ht.destroyHuffmanTree(HuffmanRaiz);
        }
        else
        {
          File << converter.to_bytes(aux) << endl << endl << "input" << i+1 << endl << endl;
          Ht.createHuffmanTree(HuffmanRaiz, minHeap[i]);
          for(auto w: minHeap[i])
          {
            t.insertBinaryTree(&raiz, make_pair(converter.to_bytes(w.first), w.second));
            AVLt.insertAVLTree(&AVLRaiz, make_pair(converter.to_bytes(w.first), w.second));
          }
          t.printBinaryTree(raiz, File);
          t.destroyBinaryTree(raiz);

          AVLt.printAVLTree(AVLRaiz, File);
          AVLt.destroyAVLTree(AVLRaiz);

          Ht.printHuffmanTree(HuffmanRaiz, File);
          Ht.destroyHuffmanTree(HuffmanRaiz);
        }
      }
    }
  }
  File.close();
  u.printHeap(minHeap[0]);
  
  return 0;
}