#include "Utils.hpp"

Utils::Utils()
{
}

wchar_t* Utils::getText(const locale& loc, string name)
{
  wifstream txt(name, ios::binary);

  if(!txt.is_open())
  {
    cerr << "Não foi possível abrir o arquivo " << name << endl;
    exit(1);
  }

  // Aplica a localização configurada ao fluxo do arquivo
  txt.imbue(loc);

  // Move o cursor para o final do arquivo para obter o tamanho
  txt.seekg(0, ios::end);

  // Obtém o tamanho do arquivo a partir da posição atual do cursor
  streampos tamanho = txt.tellg();
      
  // Move o cursor de volta para o início do arquivo
  txt.seekg(0, ios::beg);

  wchar_t* buffer = new wchar_t[tamanho];

  // Lê o conteúdo do arquivo para o buffer
  txt.read(buffer, tamanho);
  
  txt.close();

  return buffer;
}

unordered_set<wstring> Utils::getStopWords(const locale& loc)
{
  wstring word;
  unordered_set<wstring> stopwords;
  
  wifstream file("dataset/stopwords.txt");

  if(!file.is_open())
  {
    cerr << "Não foi possível abrir o arquivo!" << endl;
    exit(1);
  }

  // Aplica a localização configurada ao fluxo do arquivo
  file.imbue(loc);

  while (file >> word)
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    stopwords.insert(word);
  }

  file.close();

  return stopwords;
}

unordered_set<wstring> Utils::getInput(const locale& loc)
{
  wstring word;
  unordered_set<wstring> input;
  
  wifstream file("dataset/input.txt");

  if(!file.is_open())
  {
    cerr << "Não foi possível abrir o arquivo!" << endl;
    exit(1);
  }

  // Aplica a localização configurada ao fluxo do arquivo
  file.imbue(loc);

  while (file >> word)
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    input.insert(word);
  }

  file.close();

  return input;
}

void Utils::swapMinHeap(vector<pair<wstring, int>>& minHeap, const int& indexToRemove, const vector<pair<wstring, int>>& proxTopK, const int& auxIndex)
{
  // Substitui o elemento na posição desejada pelo novo valor
  minHeap[indexToRemove] = proxTopK[auxIndex];

  // Restaure a propriedade do heap mínimo começando na posição do novo valor
  int currentIndex = indexToRemove;
  int parentIndex = (currentIndex - 1) / 2;

  // Atualize o elemento até que ele esteja na posição correta
  while (currentIndex > 0 && minHeap[currentIndex] < minHeap[parentIndex])
  {
    swap(minHeap[currentIndex], minHeap[parentIndex]);
    currentIndex = parentIndex;
    parentIndex = (currentIndex - 1) / 2;
  }
}


void Utils::makeFrequenciesMaps(const locale& loc, const int& numFiles, vector<unordered_map<wstring, int>>& frequenceMap)
{ 
  unordered_set<wstring> stopwords = getStopWords(loc);
  wstring word;
  
  for(int i = 1; i <= numFiles; i++)
  {
    string name = "./dataset/input" + to_string(i) + ".data";
    wchar_t* txt = getText(loc, name), *ch = txt;
    unordered_map<wstring, int> dataMap;
    
    while(*ch)
    { 
      switch(*ch)
      {
        case L' ': case L'!': case L'?': case L'.': case L'\n': case L',': case L'(': case L')': case L';': case L'/': case L':': case L'—': case L'"': case L'\'':
          if(!word.empty())
          {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if(stopwords.find(word) == stopwords.end())
            {
              dataMap[word]++;
            }
            word.clear();
          }
          break;
  
        default:
          if(*ch == '-' && word.size() == 0)
          {
            break;
          }
          word += *ch;
          break;
      }
      ch++;
    }
    frequenceMap.push_back(dataMap);
    delete[] txt;
  }
}

void Utils::makeHeaps(const int& k, const int& numFiles, const vector<unordered_map <wstring, int>>& frequenceMap, vector<vector<pair<wstring, int>>>& minHeap, vector<pair<wstring, int>>& proxTopK)
{ 
  auto customComparator = [](const pair<wstring, int>& a, const pair<wstring, int>& b)
  {
    return a.second > b.second;
  };
  
  for(int i = 0; i < numFiles; i++)
  {
    vector<pair<wstring, int>> dataHeap;
    pair<wstring, int> topL;
    
    for (const auto& aux: frequenceMap[i])
    { 
      if(static_cast<int>(dataHeap.size()) < k)
      {
        dataHeap.push_back(make_pair(aux.first, aux.second));
        if(static_cast<int>(dataHeap.size()) == k)
        {
          make_heap(dataHeap.begin(), dataHeap.end(), customComparator);
        }
      }
      else
      {
        if(aux.second > dataHeap[0].second)
        {
          topL.first = dataHeap[0].first;
          topL.second = dataHeap[0].second;
          
          pop_heap(dataHeap.begin(), dataHeap.end(), customComparator);
          dataHeap.pop_back();
          dataHeap.push_back(make_pair(aux.first, aux.second));
          push_heap(dataHeap.begin(), dataHeap.end(), customComparator);
        }
      }
    }
    minHeap.push_back(dataHeap);
    proxTopK.push_back(topL);
  }
}

// void Utils::printHeap(vector<pair<wstring, int>> heap)
// {
//   wstring_convert<codecvt_utf8<wchar_t>> converter;
  
//   for (auto i = 0u; i < heap.size(); i++)
//   {
//     cout << "Palavra: " << converter.to_bytes(heap[i].first) << " --- " << "Frequência: "<< heap[i].second << endl;
//   }
// }
