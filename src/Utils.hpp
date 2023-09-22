#include <bits/stdc++.h>

#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

class Utils
{
  public:
    Utils();

    wchar_t* getText(const locale& loc, string name);
    unordered_set<wstring> getStopWords(const locale& loc);
    unordered_set<wstring> getInput(const locale& loc);
    void swapMinHeap(vector<pair<wstring, int>>& minHeap, const int& indexToRemove, const vector<pair<wstring, int>>& proxTopK, const int& indexMinHeap);
    void makeFrequenciesMaps(const locale& loc, const int& numFiles, vector<unordered_map<wstring, int>>& frequenceMap);
    // void printHeap(vector<pair<wstring, int>> heap);
    void makeHeaps(const int& k, const int& numFiles, const vector<unordered_map <wstring, int>>& frequenceMap, vector<vector<pair<wstring, int>>>& minHeap, vector<pair<wstring, int>>& proxTopK);
};

#endif
